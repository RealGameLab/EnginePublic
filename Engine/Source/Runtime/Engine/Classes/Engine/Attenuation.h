// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "UObject/Class.h"
#include "Engine/EngineTypes.h"
#include "Curves/CurveFloat.h"
#include "Attenuation.generated.h"

struct FGlobalFocusSettings;

UENUM(BlueprintType)
enum class EAttenuationDistanceModel : uint8
{
	Linear,
	Logarithmic,
	Inverse,
	LogReverse,
	NaturalSound,
	Custom,
};

UENUM(BlueprintType)
namespace EAttenuationShape
{
	enum Type
	{
		Sphere,
		Capsule,
		Box,
		Cone
	};
}

/*
* Base class for attenuation settings.
*/
USTRUCT()
struct ENGINE_API FBaseAttenuationSettings
{
	GENERATED_USTRUCT_BODY()

	virtual ~FBaseAttenuationSettings() { }

	/* The type of volume versus distance algorithm to use for the attenuation model. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attenuation )
	EAttenuationDistanceModel DistanceAlgorithm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attenuation)
	FRuntimeFloatCurve CustomAttenuationCurve;

	/* The shape of the attenuation volume. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attenuation )
	TEnumAsByte<enum EAttenuationShape::Type> AttenuationShape;

	/* The volume at maximum distance in deciBels. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attenuation, meta=(DisplayName = "dB Attenuation At Max", ClampMax = "0" ))
	float dBAttenuationAtMax;

	/* The dimensions to use for the attenuation shape. Interpretation of the values differ per shape.
	   Sphere  - X is Sphere Radius. Y and Z are unused
	   Capsule - X is Capsule Half Height, Y is Capsule Radius, Z is unused
	   Box     - X, Y, and Z are the Box's dimensions
	   Cone    - X is Cone Radius, Y is Cone Angle, Z is Cone Falloff Angle
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attenuation)
	FVector AttenuationShapeExtents;

	/* The distance back from the sound's origin to begin the cone when using the cone attenuation shape. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attenuation, meta=(ClampMin = "0"))
	float ConeOffset;

	/* The distance over which falloff occurs. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Attenuation, meta=(ClampMin = "0"))
	float FalloffDistance;

	FBaseAttenuationSettings()
		: DistanceAlgorithm(EAttenuationDistanceModel::Linear)
		, AttenuationShape(EAttenuationShape::Sphere)
		, dBAttenuationAtMax(-60.f)
		, AttenuationShapeExtents(400.f, 0.f, 0.f)
		, ConeOffset(0.f)
		, FalloffDistance(3600.f)
	{
	}

	struct AttenuationShapeDetails
	{
		FVector Extents;
		float Falloff;
		float ConeOffset;
	};

	virtual void CollectAttenuationShapesForVisualization(TMultiMap<EAttenuationShape::Type, AttenuationShapeDetails>& ShapeDetailsMap) const;
	float GetMaxDimension() const;
	float Evaluate(const FTransform& Origin, FVector Location, float DistanceScale = 1.f) const;

	float AttenuationEval(float Distance, float Falloff, float DistanceScale = 1.f) const;
	float AttenuationEvalBox(const FTransform& Origin, FVector Location, float DistanceScale = 1.f) const;
	float AttenuationEvalCapsule(const FTransform& Origin, FVector Location, float DistanceScale = 1.f) const;
	float AttenuationEvalCone(const FTransform& Origin, FVector Location, float DistanceScale = 1.f) const;
};