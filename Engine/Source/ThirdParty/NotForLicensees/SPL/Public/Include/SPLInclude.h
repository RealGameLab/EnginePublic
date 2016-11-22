/*
	Copyright Donya Labs AB 2016

*/

#pragma once

#define JSON_API

//~ Processors Json
#include "Enums.h"
#include "BaseNode.h"
#include "BaseSettings.h"
#include "BaseProcessor.h"
#include "BaseMaterialCaster.h"
#include "UnknownNode.h"
#include "SPLHeader.h"
#include "SPL.h"

//~ SPL Nodes
#include "ContainerNode.h"
#include "ProcessNode.h"
#include "WriteNode.h"

//~ Settings Objects
#include "AggregationSettings.h"
#include "BoneSettings.h"
#include "CuttingPlaneSettings.h"
#include "ImpostorSettings.h"
#include "MappingImageSettings.h"
#include "NormalCalculationSettings.h"
#include "OcclusionMeshSettings.h"
#include "ReductionSettings.h"
#include "RemeshingSettings.h"
#include "RepairSettings.h"
#include "ShadowMeshSettings.h"
#include "VisibilitySettings.h"

//~ Processors
#include "AggregationProcessor.h"
#include "ReductionProcessor.h"
#include "RemeshingProcessor.h"
#include "ImposterProcessor.h"
#include "OcclusionMeshProcessor.h"

//~ Casters
#include "AmbientOcclusionCaster.h"
#include "ColorCaster.h"
#include "DisplacementCaster.h"
#include "NormalCaster.h"
#include "OpacityCaster.h"



