#pragma once

#include "../json/json.h"

#include "BaseProcessor.h"


namespace Simplygon {
	namespace SPL {
		namespace v80 {

			class ReductionSettings;
			class MappingImageSettings;
			class NormalCalculationSettings;
			class RepairSettings;
			class VisibilitySettings;
			class BoneSettings;

			class ReductionProcessor : public BaseProcessor
			{
			public:
				ReductionSettings* ReductionSettings;
				MappingImageSettings* MappingImageSettings;
				NormalCalculationSettings* NormalCalculationSettings;
				RepairSettings* RepairSettings;
				VisibilitySettings* VisibilitySettings;
				BoneSettings* BoneSettings;

				ReductionProcessor() : BaseProcessor()
				{
					Type = "ReductionProcessor";
					ReductionSettings = nullptr;
					MappingImageSettings = nullptr;
					NormalCalculationSettings = nullptr;
					RepairSettings = nullptr;
					VisibilitySettings = nullptr;
					BoneSettings = nullptr;
				}

				ReductionProcessor(const Json::Value& jsonNode);
				~ReductionProcessor();
				virtual void ToJson(Json::Value& jsonNode);
			};
		}
	}
}