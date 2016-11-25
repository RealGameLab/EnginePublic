// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Styling/ISlateStyle.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWidget.h"
#include "Widgets/SCompoundWidget.h"
#include "Framework/Commands/UICommandList.h"

/**
 * Implements the messaging debugger toolbar widget.
 */
class SMessagingDebuggerToolbar
	: public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SMessagingDebuggerToolbar) { }
	SLATE_END_ARGS()

public:

	/**
	 * Construct this widget
	 *
	 * @param InArgs The declaration data for this widget.
	 * @param InStyle The visual style to use for this widget.
	 * @param InCommandList The command list to bind to.
	 */
	void Construct( const FArguments& InArgs, const TSharedRef<ISlateStyle>& InStyle, const TSharedRef<FUICommandList>& InCommandList );

protected:

	/**
	 * Creates the toolbar widget.
	 *
	 * @param CommandList The command list to use for the toolbar buttons.
	 * @return The toolbar widget.
	 */
	TSharedRef<SWidget> MakeToolbar( const TSharedRef<FUICommandList>& CommandList );
};
