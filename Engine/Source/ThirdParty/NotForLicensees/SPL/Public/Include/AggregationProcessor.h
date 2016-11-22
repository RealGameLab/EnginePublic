#pragma once

#include "../json/json.h"

#include "BaseProcessor.h"
#include "BaseSettings.h"


namespace Simplygon {
	namespace SPL {
		namespace v80 {

			class AggregationSettings;
			class MappingImageSettings;
			class VisibilitySettings;

			class AggregationProcessor : public BaseProcessor
			{
			public:
				AggregationSettings* AggregationSettings;
				MappingImageSettings* MappingImageSettings;
				VisibilitySettings* VisibilitySettings;

				AggregationProcessor() : BaseProcessor()
				{
					Type = "AggregationProcessor";
					AggregationSettings = nullptr;
					MappingImageSettings = nullptr;
					VisibilitySettings = nullptr;
				}

				AggregationProcessor(const Json::Value& jsonNode);
				~AggregationProcessor();

				virtual void ToJson(Json::Value& jsonNode);
			};
		}
	}
}