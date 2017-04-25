// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "INiagaraEditorTypeUtilities.h"

class SNiagaraParameterEditor;

/** Niagara editor utilities for the bool type. */
class FNiagaraEditorColorTypeUtilities : public FNiagaraEditorTypeUtilities
{
public:
	//~ INiagaraEditorTypeUtilities interface.
	virtual bool CanProvideDefaultValue() const override { return true; }
	virtual void UpdateStructWithDefaultValue(TSharedRef<FStructOnScope> Struct) const override;
	virtual bool CanCreateParameterEditor() const override { return true; }
	virtual TSharedPtr<SNiagaraParameterEditor> CreateParameterEditor() const override;
};