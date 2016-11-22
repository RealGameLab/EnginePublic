#pragma once

#include "../json/json.h"

#include "BaseProcessor.h"

namespace Simplygon {
	namespace SPL {
		namespace v80 {

			class OcclusionMeshSettings;

			class  OcclusionMeshProcessor : public BaseProcessor
			{
			public:
				OcclusionMeshSettings* OcclusionMeshSettings;

				OcclusionMeshProcessor() : BaseProcessor()
				{
					Type = "OcclusionMeshProcessor";
					OcclusionMeshSettings = nullptr;
				}

				OcclusionMeshProcessor(const Json::Value& jsonNode);
				~OcclusionMeshProcessor();

				virtual void ToJson(Json::Value& jsonNode);
			};
		}
	}
}