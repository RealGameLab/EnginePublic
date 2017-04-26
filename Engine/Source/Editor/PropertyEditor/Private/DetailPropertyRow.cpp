// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DetailPropertyRow.h"
#include "Modules/ModuleManager.h"
#include "PropertyCustomizationHelpers.h"
#include "UserInterface/PropertyEditor/SResetToDefaultPropertyEditor.h"
#include "DetailItemNode.h"
#include "DetailCategoryGroupNode.h"
#include "CustomChildBuilder.h"

#define LOCTEXT_NAMESPACE	"DetailPropertyRow"

FDetailPropertyRow::FDetailPropertyRow(TSharedPtr<FPropertyNode> InPropertyNode, TSharedRef<FDetailCategoryImpl> InParentCategory, TSharedPtr<FPropertyNode> InExternalRootNode )
	: CustomIsEnabledAttrib( true )
	, PropertyNode( InPropertyNode )
	, ParentCategory( InParentCategory )
	, ExternalRootNode( InExternalRootNode )
	, bShowPropertyButtons( true )
	, bShowCustomPropertyChildren( true )
	, bForceAutoExpansion( false )
{
	if( InPropertyNode.IsValid() )
	{
		TSharedRef<FPropertyNode> PropertyNodeRef = PropertyNode.ToSharedRef();

		PropertyHandle = InParentCategory->GetParentLayoutImpl().GetPropertyHandle(PropertyNodeRef);

		const TSharedRef<IPropertyUtilities> Utilities = InParentCategory->GetParentLayoutImpl().GetPropertyUtilities();

		if (PropertyNode->AsCategoryNode() == NULL)
		{
			MakePropertyEditor(PropertyNodeRef, Utilities, PropertyEditor);
		}

		if (PropertyNode->GetPropertyKeyNode().IsValid())
		{
			UStructProperty* KeyStructProp = Cast<UStructProperty>(PropertyNode->GetPropertyKeyNode()->GetProperty());

			// Only struct and customized properties require their own nodes. Everything else just needs a property editor.
			bool bNeedsKeyPropEditor = KeyStructProp == nullptr && !GetPropertyCustomization(PropertyNode->GetPropertyKeyNode().ToSharedRef(), InParentCategory).IsValid();

			if ( bNeedsKeyPropEditor )
			{
				MakePropertyEditor(PropertyNode->GetPropertyKeyNode().ToSharedRef(), Utilities, PropertyKeyEditor);
			}
		}

		CustomTypeInterface = GetPropertyCustomization(PropertyNodeRef, InParentCategory);
	}
}

IDetailPropertyRow& FDetailPropertyRow::DisplayName( const FText& InDisplayName )
{
	if (PropertyNode.IsValid())
	{
		PropertyNode->SetDisplayNameOverride( InDisplayName );
	}
	return *this;
}

IDetailPropertyRow& FDetailPropertyRow::ToolTip( const FText& InToolTip )
{
	if (PropertyNode.IsValid())
	{
		PropertyNode->SetToolTipOverride( InToolTip );
	}
	return *this;
}

IDetailPropertyRow& FDetailPropertyRow::ShowPropertyButtons( bool bInShowPropertyButtons )
{
	bShowPropertyButtons = bInShowPropertyButtons;
	return *this;
}

IDetailPropertyRow& FDetailPropertyRow::EditCondition( TAttribute<bool> EditConditionValue, FOnBooleanValueChanged OnEditConditionValueChanged )
{
	CustomEditCondition = MakeShareable( new FCustomEditCondition );

	CustomEditCondition->EditConditionValue = EditConditionValue;
	CustomEditCondition->OnEditConditionValueChanged = OnEditConditionValueChanged;
	return *this;
}

IDetailPropertyRow& FDetailPropertyRow::IsEnabled( TAttribute<bool> InIsEnabled )
{
	CustomIsEnabledAttrib = InIsEnabled;
	return *this;
}

IDetailPropertyRow& FDetailPropertyRow::ShouldAutoExpand(bool bInForceExpansion)
{
	bForceAutoExpansion = bInForceExpansion;
	return *this;
}

IDetailPropertyRow& FDetailPropertyRow::Visibility( TAttribute<EVisibility> Visibility )
{
	PropertyVisibility = Visibility;
	return *this;
}

IDetailPropertyRow& FDetailPropertyRow::OverrideResetToDefault(const FResetToDefaultOverride& ResetToDefault)
{
	CustomResetToDefault = ResetToDefault;
	return *this;
}

void FDetailPropertyRow::GetDefaultWidgets( TSharedPtr<SWidget>& OutNameWidget, TSharedPtr<SWidget>& OutValueWidget ) 
{
	FDetailWidgetRow Row;
	GetDefaultWidgets(OutNameWidget, OutValueWidget, Row);
}

void FDetailPropertyRow::GetDefaultWidgets( TSharedPtr<SWidget>& OutNameWidget, TSharedPtr<SWidget>& OutValueWidget, FDetailWidgetRow& Row )
{
	TSharedPtr<FDetailWidgetRow> CustomTypeRow;
	if ( CustomTypeInterface.IsValid() ) 
	{
		CustomTypeRow = MakeShareable(new FDetailWidgetRow);

		CustomTypeInterface->CustomizeHeader(PropertyHandle.ToSharedRef(), *CustomTypeRow, *this);
	}

	const bool bAddWidgetDecoration = false;
	MakeNameOrKeyWidget(Row,CustomTypeRow);
	MakeValueWidget(Row,CustomTypeRow,bAddWidgetDecoration);

	OutNameWidget = Row.NameWidget.Widget;
	OutValueWidget = Row.ValueWidget.Widget;
}

bool FDetailPropertyRow::HasColumns() const
{
	// Regular properties always have columns
	return !CustomPropertyWidget.IsValid() || CustomPropertyWidget->HasColumns();
}

bool FDetailPropertyRow::ShowOnlyChildren() const
{
	return PropertyTypeLayoutBuilder.IsValid() && CustomPropertyWidget.IsValid() && !CustomPropertyWidget->HasAnyContent();
}

bool FDetailPropertyRow::RequiresTick() const
{
	return PropertyVisibility.IsBound();
}

FDetailWidgetRow& FDetailPropertyRow::CustomWidget( bool bShowChildren )
{
	bShowCustomPropertyChildren = bShowChildren;
	CustomPropertyWidget = MakeShareable( new FDetailWidgetRow );
	return *CustomPropertyWidget;
}

TSharedPtr<FAssetThumbnailPool> FDetailPropertyRow::GetThumbnailPool() const
{
	TSharedPtr<FDetailCategoryImpl> ParentCategoryPinned = ParentCategory.Pin();
	return ParentCategoryPinned.IsValid() ? ParentCategoryPinned->GetParentLayout().GetThumbnailPool() : NULL;
}

TSharedPtr<IPropertyUtilities> FDetailPropertyRow::GetPropertyUtilities() const
{
	TSharedPtr<FDetailCategoryImpl> ParentCategoryPinned = ParentCategory.Pin();
	if (ParentCategoryPinned.IsValid())
	{
		return ParentCategoryPinned->GetParentLayout().GetPropertyUtilities();
	}
	
	return nullptr;
}

FDetailWidgetRow FDetailPropertyRow::GetWidgetRow()
{
	if( HasColumns() )
	{
		FDetailWidgetRow Row;
	
		MakeNameOrKeyWidget( Row, CustomPropertyWidget );
		MakeValueWidget( Row, CustomPropertyWidget );

		return Row;
	}
	else
	{
		return *CustomPropertyWidget;
	}
}

void FDetailPropertyRow::OnItemNodeInitialized( TSharedRef<FDetailCategoryImpl> InParentCategory, const TAttribute<bool>& InIsParentEnabled, TSharedPtr<IDetailGroup> InParentGroup)
{
	IsParentEnabled = InIsParentEnabled;

	// Don't customize the user already customized
	if( !CustomPropertyWidget.IsValid() && CustomTypeInterface.IsValid() )
	{
		CustomPropertyWidget = MakeShareable(new FDetailWidgetRow);

		CustomTypeInterface->CustomizeHeader(PropertyHandle.ToSharedRef(), *CustomPropertyWidget, *this);

		// set initial value of enabled attribute to settings from struct customization
		if (CustomPropertyWidget->IsEnabledAttr.IsBound())
		{
			CustomIsEnabledAttrib = CustomPropertyWidget->IsEnabledAttr;
		}
	}

	if( bShowCustomPropertyChildren && CustomTypeInterface.IsValid() )
	{
		PropertyTypeLayoutBuilder = MakeShareable(new FCustomChildrenBuilder(InParentCategory, InParentGroup));

		/** Does this row pass its custom reset behavior to its children? */
		if (CustomResetToDefault.IsSet() && CustomResetToDefault->PropagatesToChildren())
		{
			PropertyTypeLayoutBuilder->OverrideResetChildrenToDefault(CustomResetToDefault.GetValue());
		}

		CustomTypeInterface->CustomizeChildren(PropertyHandle.ToSharedRef(), *PropertyTypeLayoutBuilder, *this);
	}
}

void FDetailPropertyRow::OnGenerateChildren( FDetailNodeList& OutChildren )
{
	if( PropertyNode->AsCategoryNode() || PropertyNode->GetProperty() )
	{
		GenerateChildrenForPropertyNode( PropertyNode, OutChildren );
	}
}

void FDetailPropertyRow::GenerateChildrenForPropertyNode( TSharedPtr<FPropertyNode>& RootPropertyNode, FDetailNodeList& OutChildren )
{
	// Children should be disabled if we are disabled
	TAttribute<bool> ParentEnabledState = CustomIsEnabledAttrib;
	if( IsParentEnabled.IsBound() || HasEditCondition() )
	{
		// Bind a delegate to the edit condition so our children will be disabled if the edit condition fails
		ParentEnabledState.Bind( this, &FDetailPropertyRow::GetEnabledState );
	}

	if( PropertyTypeLayoutBuilder.IsValid() && bShowCustomPropertyChildren )
	{
		const TArray< FDetailLayoutCustomization >& ChildRows = PropertyTypeLayoutBuilder->GetChildCustomizations();

		for( int32 ChildIndex = 0; ChildIndex < ChildRows.Num(); ++ChildIndex )
		{
			TSharedRef<FDetailItemNode> ChildNodeItem = MakeShareable( new FDetailItemNode( ChildRows[ChildIndex], ParentCategory.Pin().ToSharedRef(), ParentEnabledState ) );
			ChildNodeItem->Initialize();
			OutChildren.Add( ChildNodeItem );
		}
	}
	else if (bShowCustomPropertyChildren || !CustomPropertyWidget.IsValid() )
	{
		TSharedRef<FDetailCategoryImpl> ParentCategoryRef = ParentCategory.Pin().ToSharedRef();
		IDetailLayoutBuilder& LayoutBuilder = ParentCategoryRef->GetParentLayout();
		UProperty* ParentProperty = RootPropertyNode->GetProperty();

		const bool bStructProperty = ParentProperty && ParentProperty->IsA<UStructProperty>();
		const bool bMapProperty = ParentProperty && ParentProperty->IsA<UMapProperty>();
		const bool bSetProperty = ParentProperty && ParentProperty->IsA<USetProperty>();

		for( int32 ChildIndex = 0; ChildIndex < RootPropertyNode->GetNumChildNodes(); ++ChildIndex )
		{
			TSharedPtr<FPropertyNode> ChildNode = RootPropertyNode->GetChildNode(ChildIndex);

			if( ChildNode.IsValid() && ChildNode->HasNodeFlags( EPropertyNodeFlags::IsCustomized ) == 0 )
			{
				if( ChildNode->AsObjectNode() )
				{
					// Skip over object nodes and generate their children.  Object nodes are not visible
					GenerateChildrenForPropertyNode( ChildNode, OutChildren );
				}
				// Only struct children can have custom visibility that is different from their parent.
				else if ( !bStructProperty || LayoutBuilder.IsPropertyVisible( FPropertyAndParent(*ChildNode->GetProperty(), ParentProperty ) ) )
				{	
					TArray<TSharedRef<IDetailTreeNode>> PropNodes;
					bool bHasKeyNode = false;

					// Create and initialize the child first
					FDetailLayoutCustomization Customization;
					Customization.PropertyRow = MakeShareable(new FDetailPropertyRow(ChildNode, ParentCategoryRef));
					TSharedRef<FDetailItemNode> ChildNodeItem = MakeShareable(new FDetailItemNode(Customization, ParentCategoryRef, ParentEnabledState));
					ChildNodeItem->Initialize();

					if ( ChildNode->GetPropertyKeyNode().IsValid() )
					{
						// If the child has a key property, only create a second node for the key if the child did not already create a property
						// editor for it
						if ( !Customization.PropertyRow->PropertyKeyEditor.IsValid() )
						{
							FDetailLayoutCustomization KeyCustom;
							KeyCustom.PropertyRow = MakeShareable(new FDetailPropertyRow(ChildNode->GetPropertyKeyNode(), ParentCategoryRef));
							TSharedRef<FDetailItemNode> KeyNodeItem = MakeShareable(new FDetailItemNode(KeyCustom, ParentCategoryRef, ParentEnabledState));
							KeyNodeItem->Initialize();
							
							PropNodes.Add(KeyNodeItem);
							bHasKeyNode = true;
						}
					}

					// Add the child node 
					PropNodes.Add(ChildNodeItem);
					
					// For set properties, set the name override to match the index
					if (bSetProperty)
					{
						ChildNode->SetDisplayNameOverride(FText::AsNumber(ChildIndex));
					}

					if (bMapProperty && bHasKeyNode)
					{
						// Group the key/value nodes for map properties
						static FText KeyValueGroupNameFormat = LOCTEXT("KeyValueGroupName", "Element {0}");
						FText KeyValueGroupName = FText::Format(KeyValueGroupNameFormat, ChildIndex);

						TSharedRef<FDetailCategoryGroupNode> KeyValueGroupNode = MakeShareable(new FDetailCategoryGroupNode(PropNodes, FName(*KeyValueGroupName.ToString()), ParentCategoryRef.Get()));
						KeyValueGroupNode->SetShowBorder(false);
						KeyValueGroupNode->SetHasSplitter(true);

						OutChildren.Add(KeyValueGroupNode);
					}
					else
					{
						OutChildren.Append(PropNodes);
					}
				}
			}
		}
	}
}


TSharedRef<FPropertyEditor> FDetailPropertyRow::MakePropertyEditor(const TSharedRef<FPropertyNode>& InPropertyNode, const TSharedRef<IPropertyUtilities>& PropertyUtilities, TSharedPtr<FPropertyEditor>& InEditor )
{
	if( !InEditor.IsValid() )
	{
		InEditor = FPropertyEditor::Create( InPropertyNode, PropertyUtilities );
	}

	return InEditor.ToSharedRef();
}

TSharedPtr<IPropertyTypeCustomization> FDetailPropertyRow::GetPropertyCustomization(const TSharedRef<FPropertyNode>& InPropertyNode, const TSharedRef<FDetailCategoryImpl>& InParentCategory)
{
	TSharedPtr<IPropertyTypeCustomization> CustomInterface;

	if (!PropertyEditorHelpers::IsStaticArray(*InPropertyNode))
	{
		UProperty* Property = InPropertyNode->GetProperty();
		TSharedPtr<IPropertyHandle> PropHandle = InParentCategory->GetParentLayoutImpl().GetPropertyHandle(InPropertyNode);

		static FName NAME_PropertyEditor("PropertyEditor");
		FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>(NAME_PropertyEditor);

		IDetailsViewPrivate& DetailsView = InParentCategory->GetDetailsView();

		TSharedRef<IDetailsView> DetailsViewPtr = StaticCastSharedRef<IDetailsView>(DetailsView.AsShared());

		FPropertyTypeLayoutCallback LayoutCallback = PropertyEditorModule.GetPropertyTypeCustomization(Property, *PropHandle, DetailsViewPtr);
		if (LayoutCallback.IsValid())
		{
			if (PropHandle->IsValidHandle())
			{
				CustomInterface = LayoutCallback.GetCustomizationInstance();
			}
		}
	}

	return CustomInterface;
}

bool FDetailPropertyRow::HasEditCondition() const
{
	return ( PropertyEditor.IsValid() && PropertyEditor->HasEditCondition() ) || CustomEditCondition.IsValid();
}

bool FDetailPropertyRow::GetEnabledState() const
{
	bool Result = IsParentEnabled.Get();

	if( HasEditCondition() ) 
	{
		if (CustomEditCondition.IsValid())
		{
			Result = Result && CustomEditCondition->EditConditionValue.Get();
		}
		else
		{
			Result = Result && PropertyEditor->IsEditConditionMet();
		}
	}
	
	Result = Result && CustomIsEnabledAttrib.Get();

	return Result;
}

bool FDetailPropertyRow::GetForceAutoExpansion() const
{
	return bForceAutoExpansion;
}

void FDetailPropertyRow::MakeNameOrKeyWidget( FDetailWidgetRow& Row, const TSharedPtr<FDetailWidgetRow> InCustomRow ) const
{
	EVerticalAlignment VerticalAlignment = VAlign_Center;
	EHorizontalAlignment HorizontalAlignment = HAlign_Fill;

	// We will only use key widgets for non-struct keys
	const bool bHasKeyNode = PropertyKeyEditor.IsValid();

	if( !bHasKeyNode && InCustomRow.IsValid() )
	{
		VerticalAlignment = InCustomRow->NameWidget.VerticalAlignment;
		HorizontalAlignment = InCustomRow->NameWidget.HorizontalAlignment;
	}

	TAttribute<bool> IsEnabledAttrib = CustomIsEnabledAttrib;

	TSharedRef<SHorizontalBox> NameHorizontalBox = SNew( SHorizontalBox );
	
	if( HasEditCondition() )
	{
		IsEnabledAttrib.Bind( this, &FDetailPropertyRow::GetEnabledState );

		NameHorizontalBox->AddSlot()
		.AutoWidth()
		.Padding( 0.0f, 0.0f )
		.VAlign(VAlign_Center)
		[
			SNew( SEditConditionWidget, PropertyEditor )
			.CustomEditCondition( CustomEditCondition.IsValid() ? *CustomEditCondition : FCustomEditCondition() )
		];
	}

	TSharedPtr<SWidget> NameWidget;

	// Key nodes take precedence over custom rows
	if ( bHasKeyNode )
	{
		const TSharedRef<IPropertyUtilities> PropertyUtilities = ParentCategory.Pin()->GetParentLayoutImpl().GetPropertyUtilities();

		NameWidget =
			SNew(SPropertyValueWidget, PropertyKeyEditor, PropertyUtilities)
			.IsEnabled(IsEnabledAttrib)
			.ShowPropertyButtons(false);
	}
	else if( InCustomRow.IsValid() )
	{
		NameWidget = 
			SNew( SBox )
			.IsEnabled( IsEnabledAttrib )
			[
				InCustomRow->NameWidget.Widget
			];
	}
	else
	{
		NameWidget = 
			SNew( SPropertyNameWidget, PropertyEditor )
			.IsEnabled( IsEnabledAttrib )
			.DisplayResetToDefault( false );
	}

	SHorizontalBox::FSlot& Slot = NameHorizontalBox->AddSlot()
	[
		NameWidget.ToSharedRef()
	];

	if (bHasKeyNode)
	{
		Slot.Padding(0.0f, 0.0f, 2.0f, 0.0f);
	}
	else if (InCustomRow.IsValid())
	{
		//Allow custom name slot to fill all the area. If the user add a SHorizontalBox with left and right align slot
		Slot.FillWidth(1.0f);
	}
	else
	{
		Slot.AutoWidth();
	}

	Row.NameContent()
	.HAlign( HorizontalAlignment )
	.VAlign( VerticalAlignment )
	[
		NameHorizontalBox
	];
}

void FDetailPropertyRow::MakeValueWidget( FDetailWidgetRow& Row, const TSharedPtr<FDetailWidgetRow> InCustomRow, bool bAddWidgetDecoration ) const
{
	EVerticalAlignment VerticalAlignment = VAlign_Center;
	EHorizontalAlignment HorizontalAlignment = HAlign_Left;

	TOptional<float> MinWidth;
	TOptional<float> MaxWidth;

	if( InCustomRow.IsValid() )
	{
		VerticalAlignment = InCustomRow->ValueWidget.VerticalAlignment;
		HorizontalAlignment = InCustomRow->ValueWidget.HorizontalAlignment;
	}

	TAttribute<bool> IsEnabledAttrib = CustomIsEnabledAttrib;
	if( HasEditCondition() )
	{
		IsEnabledAttrib.Bind( this, &FDetailPropertyRow::GetEnabledState );
	}

	TSharedRef<SHorizontalBox> ValueWidget = 
		SNew( SHorizontalBox )
		.IsEnabled( IsEnabledAttrib );

	if( InCustomRow.IsValid() )
	{
		MinWidth = InCustomRow->ValueWidget.MinWidth;
		MaxWidth = InCustomRow->ValueWidget.MaxWidth;

		ValueWidget->AddSlot()
		[
			InCustomRow->ValueWidget.Widget
		];
	}
	else
	{
		TSharedPtr<SPropertyValueWidget> PropertyValue;

		ValueWidget->AddSlot()
		.Padding( 0.0f, 0.0f, 4.0f, 0.0f )
		[
			SAssignNew( PropertyValue, SPropertyValueWidget, PropertyEditor, GetPropertyUtilities() )
			.ShowPropertyButtons( false ) // We handle this ourselves
		];

		MinWidth = PropertyValue->GetMinDesiredWidth();
		MaxWidth = PropertyValue->GetMaxDesiredWidth();
	}

	if(bAddWidgetDecoration)
	{
		if( bShowPropertyButtons )
		{
			TArray< TSharedRef<SWidget> > RequiredButtons;
			PropertyEditorHelpers::MakeRequiredPropertyButtons( PropertyEditor.ToSharedRef(), /*OUT*/RequiredButtons );

			for( int32 ButtonIndex = 0; ButtonIndex < RequiredButtons.Num(); ++ButtonIndex )
			{
				ValueWidget->AddSlot()
				.AutoWidth()
				.HAlign(HAlign_Left)
				.VAlign(VAlign_Center)
				.Padding(2.0f, 1.0f)
				[ 
					RequiredButtons[ButtonIndex]
				];
			}
		}

		if (PropertyHandle->HasMetaData(TEXT("ConfigHierarchyEditable")))
		{
			ValueWidget->AddSlot()
			.AutoWidth()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Left)
			.Padding(0.0f, 0.0f, 4.0f, 0.0f)
			[
				PropertyCustomizationHelpers::MakeEditConfigHierarchyButton(FSimpleDelegate::CreateSP(PropertyEditor.ToSharedRef(), &FPropertyEditor::EditConfigHierarchy))
			];
		}

		if (!PropertyHandle->HasMetaData(TEXT("NoResetToDefault")))
		{
			ValueWidget->AddSlot()
			.Padding( 2.0f, 0.0f )
			.AutoWidth()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Left)
			[
				SNew( SResetToDefaultPropertyEditor, PropertyEditor.ToSharedRef() )
				.IsEnabled( IsEnabledAttrib )
				.CustomResetToDefault(CustomResetToDefault)
			];
		}
	}

	Row.ValueContent()
	.HAlign( HorizontalAlignment )
	.VAlign( VerticalAlignment )	
	.MinDesiredWidth( MinWidth )
	.MaxDesiredWidth( MaxWidth )
	[
		ValueWidget
	];
}

#undef LOCTEXT_NAMESPACE
