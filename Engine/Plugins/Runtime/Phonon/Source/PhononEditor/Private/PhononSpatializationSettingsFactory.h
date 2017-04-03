// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "IAudioExtensionPlugin.h"
#include "AssetToolsModule.h"
#include "Factories/Factory.h"
#include "AssetTypeActions_Base.h"
#include "PhononSpatializationSettingsFactory.generated.h"

class FAssetTypeActions_PhononSpatializationSettings : public FAssetTypeActions_Base
{
public:
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_PhononSpatializationSettings", "Phonon Source Spatialization Settings"); }
	virtual FColor GetTypeColor() const override { return FColor(245, 195, 101); }
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override { return EAssetTypeCategories::Sounds; }
};

UCLASS(MinimalAPI, hidecategories = Object)
class UPhononSpatializationSettingsFactory : public UFactory
{
	GENERATED_UCLASS_BODY()

		//~ Begin UFactory Interface
		virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	//~ Begin UFactory Interface	
};

