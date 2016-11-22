#pragma once

#include "../json/json.h"

#include "BaseProcessor.h"

namespace Simplygon {
	namespace SPL {
		namespace v80 {

			class ImpostorSettings;
			class MappingImageSettings;

			class  ImposterProcessor : public BaseProcessor
			{
			public:
				ImpostorSettings* ImpostorSettings;
				MappingImageSettings* MappingImageSettings;

				ImposterProcessor() : BaseProcessor()
				{
					Type = "ImposterProcessor";
					ImpostorSettings = nullptr;
					MappingImageSettings = nullptr;
				}

				ImposterProcessor(const Json::Value& jsonNode);
				~ImposterProcessor();
				virtual void ToJson(Json::Value& jsonNode);
			};
		}
	}
}