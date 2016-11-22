#pragma once

#include "../json/json.h"

#include "BaseProcessor.h"

namespace Simplygon {
	namespace SPL {
		namespace v80 {

			class RemeshingSettings;
			class MappingImageSettings;
			class VisibilitySettings;
			class BoneSettings;
			class CuttingPlaneSettings;

			class RemeshingProcessor : public BaseProcessor
			{
			public:
				RemeshingSettings* RemeshingSettings;
				MappingImageSettings* MappingImageSettings;
				VisibilitySettings* VisibilitySettings;
				BoneSettings* BoneSettings;
				CuttingPlaneSettings* CuttingPlaneSettings;

				RemeshingProcessor() : BaseProcessor()
				{
					Type = "RemeshingProcessor";
					RemeshingSettings = nullptr;
					MappingImageSettings = nullptr;
					VisibilitySettings = nullptr;
					BoneSettings = nullptr;
					CuttingPlaneSettings = nullptr;
				}

				RemeshingProcessor(const Json::Value& jsonNode);
				~RemeshingProcessor();
				virtual void ToJson(Json::Value& jsonNode);
			};
		}
	}
}