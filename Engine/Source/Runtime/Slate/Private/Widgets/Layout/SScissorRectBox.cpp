// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Widgets/Layout/SScissorRectBox.h"
#include "Types/PaintArgs.h"
#include "Layout/ArrangedChildren.h"
#include "Rendering/RenderingCommon.h"
#include "IConsoleManager.h"

namespace Slate
{
	static FAutoConsoleVariable OverrideScissorRect( TEXT( "Slate.OverrideScissorRect" ), 1, TEXT( "Whether to allow Slate to apply a scissor clip to UI elements to prevent certain artifacts.  You might need to disable this if you are drawing UI over a mirror backbuffer while in VR." ) );
}

SScissorRectBox::SScissorRectBox()
{
}

void SScissorRectBox::Construct(const FArguments& InArgs)
{
	bCanTick = false;

	ChildSlot
	[
		InArgs._Content.Widget
	];
}

FVector2D SScissorRectBox::ComputeDesiredSize( float ) const
{
	EVisibility ChildVisibility = ChildSlot.GetWidget()->GetVisibility();

	if (ChildVisibility != EVisibility::Collapsed)
	{
		return ChildSlot.GetWidget()->GetDesiredSize();
	}
	
	return FVector2D::ZeroVector;
}

void SScissorRectBox::OnArrangeChildren(const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren) const
{
	// the child takes up the full space of this panel, always.
	ArrangedChildren.AddWidget(AllottedGeometry.MakeChild(ChildSlot.GetWidget(), AllottedGeometry.GetLocalSize(), FSlateLayoutTransform()));
}

FChildren* SScissorRectBox::GetChildren()
{
	return &ChildSlot;
}

int32 SScissorRectBox::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	// just draw the only child
	FArrangedChildren ArrangedChildren(EVisibility::Visible);
	{
		this->ArrangeChildren(AllottedGeometry, ArrangedChildren);
	}

	// Maybe none of our children are visible
	if( ArrangedChildren.Num() > 0 )
	{
		check( ArrangedChildren.Num() == 1 );
		FArrangedWidget& TheChild = ArrangedChildren[0];

		// set the hacky, back door global scissor rect settings.
		// This will get picked up by the element batcher and added to the draw element.
		// We do it this way because this scissor rect is a real hack until better solution is made available.
		// In the meantime, we don't want to modify the public interface of all element drawing to ensure all widgets pick up this scissor rect.
		extern SLATECORE_API TOptional<FShortRect> GSlateScissorRect;
		TOptional<FShortRect> OldRect = GSlateScissorRect;
		const bool bOverrideScissorRect = Slate::OverrideScissorRect->GetInt() != 0;
		if( bOverrideScissorRect )
		{
			// Child clipping rect is made effectively infinite to ensure that any rotated children do not get prematurely cut off. We let the scissor rect do all the work.
			const FSlateRect ChildClippingRect = AllottedGeometry.GetClippingRect().IntersectionWith( MyClippingRect );
			GSlateScissorRect = FShortRect(ChildClippingRect);
		}
		int32 Result = TheChild.Widget->Paint( Args.WithNewParent(this), TheChild.Geometry, FSlateRect(FVector2D(-FLT_MAX, -FLT_MAX), FVector2D(FLT_MAX, FLT_MAX)), OutDrawElements, LayerId, InWidgetStyle, ShouldBeEnabled( bParentEnabled ) );

		if( bOverrideScissorRect )
		{
			// We've added all the draw elements, so put the scissor rect back
			GSlateScissorRect = OldRect;
		}
		
		return Result;
	}

	return LayerId;
}

void SScissorRectBox::SetContent(const TSharedRef< SWidget >& InContent)
{
	ChildSlot
	[
		InContent
	];
}
