// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

/*=============================================================================
	StaticBoundShaderState.h: Static bound shader state definitions.
=============================================================================*/

#pragma once

#include "CoreMinimal.h"
#include "Containers/List.h"
#include "RenderResource.h"

class FShader;

/**
 * FGlobalBoundShaderState
 * 
 * Encapsulates a global bound shader state resource.
 */
class FGlobalBoundShaderStateResource : public FRenderResource
{
public:

	/** @return The list of global bound shader states. */
	SHADERCORE_API static TLinkedList<FGlobalBoundShaderStateResource*>*& GetGlobalBoundShaderStateList();

	/** Initialization constructor. */
	SHADERCORE_API FGlobalBoundShaderStateResource();

	/** Destructor. */
	SHADERCORE_API virtual ~FGlobalBoundShaderStateResource();

	/**
	 * If this global bound shader state hasn't been initialized yet, initialize it.
	 * @return The bound shader state RHI.
	 */
	FBoundShaderStateRHIParamRef GetInitializedRHI(
		FVertexDeclarationRHIParamRef VertexDeclaration, 
		FVertexShaderRHIParamRef VertexShader, 
		FPixelShaderRHIParamRef PixelShader,
		FGeometryShaderRHIParamRef GeometryShader
		);

	/**
	 * If this global bound shader state has been initialized return it, otherwise return null. Can be called from any thread.
	 * @return The bound shader state RHI.
	 */
	FBoundShaderStateRHIParamRef GetPreinitializedRHI();

private:

	/** The cached bound shader state. */
	FBoundShaderStateRHIRef BoundShaderState;

	/** This resource's link in the list of global bound shader states. */
	TLinkedList<FGlobalBoundShaderStateResource*> GlobalListLink;

	// FRenderResource interface.
	SHADERCORE_API virtual void ReleaseRHI();

#if DO_CHECK
	FVertexDeclarationRHIParamRef BoundVertexDeclaration;
	FVertexShaderRHIParamRef BoundVertexShader;
	FPixelShaderRHIParamRef BoundPixelShader;
	FGeometryShaderRHIParamRef BoundGeometryShader;
#endif 
};

typedef TGlobalResource<FGlobalBoundShaderStateResource> FGlobalBoundShaderState_Internal;


struct FGlobalBoundShaderStateArgs
{
	FVertexDeclarationRHIParamRef VertexDeclarationRHI;
	FShader* VertexShader;
	FShader* PixelShader;
	FShader* GeometryShader;
};

struct FGlobalBoundShaderStateWorkArea
{
	FGlobalBoundShaderStateArgs Args;
	FGlobalBoundShaderState_Internal* BSS; //ideally this would be part of this memory block and not a separate allocation...that is doable, if a little tedious. The point is we need to delay the construction until we get back to the render thread.

	FGlobalBoundShaderStateWorkArea()
		: BSS(nullptr)
	{
	}
};

struct FGlobalBoundShaderState
{
public:

	FGlobalBoundShaderStateWorkArea* Get(ERHIFeatureLevel::Type InFeatureLevel)  { return WorkAreas[InFeatureLevel]; }
	FGlobalBoundShaderStateWorkArea** GetPtr(ERHIFeatureLevel::Type InFeatureLevel)  { return &WorkAreas[InFeatureLevel]; }

private:

	FGlobalBoundShaderStateWorkArea* WorkAreas[ERHIFeatureLevel::Num];
};



/**
 * SetGlobalBoundShaderState - sets the global bound shader state, also creates and caches it if necessary
 *
 * @param RHICmdList				- cmdlist to add to
 * @param BoundShaderState			- current bound shader state, will be updated if it wasn't a valid ref
 * @param VertexDeclaration			- the vertex declaration to use in creating the new bound shader state
 * @param VertexShader				- the vertex shader to use in creating the new bound shader state
 * @param PixelShader				- the pixel shader to use in creating the new bound shader state
 * @param GeometryShader			- the geometry shader to use in creating the new bound shader state (0 if not used)
 */

DEPRECATED(4.15, "Use functionality in PipelineStateCache.h")
SHADERCORE_API void SetGlobalBoundShaderState(
	FRHICommandList& RHICmdList,
	ERHIFeatureLevel::Type FeatureLevel,
	FGlobalBoundShaderState& BoundShaderState,
	FVertexDeclarationRHIParamRef VertexDeclaration,
	FShader* VertexShader,
	FShader* PixelShader,
	FShader* GeometryShader = nullptr
	);
