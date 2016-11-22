#pragma once

#include "../json/json.h"

using namespace std;

namespace Simplygon {
	namespace SPL {
		namespace v80 {
			class  BaseSettings
			{
			protected:
				BaseSettings()
				{
				}

				BaseSettings(const Json::Value& jsonNode)
				{
					Enabled = jsonNode["Enabled"].asBool();
				}
			public:
				bool Enabled;

				virtual ~BaseSettings()
				{
				}

				virtual void ToJson(Json::Value& jsonNode)
				{
					jsonNode["Enabled"] = Enabled;
				}

				static BaseSettings* ParseJson(const Json::Value& jsonNode, string type);
			};
		}
	}
}
