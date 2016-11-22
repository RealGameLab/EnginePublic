#pragma once

#include "../json/json.h"

using namespace std;

namespace Simplygon {
	namespace SPL {
		namespace v80 {

			class  BaseMaterialCaster
			{
			protected:
				BaseMaterialCaster()
				{
				}

				BaseMaterialCaster(const Json::Value& jsonNode)
				{
					Type = jsonNode["Type"].asString();
					Name = jsonNode["Name"].asString();
					Channel = jsonNode["Channel"].asString();
					Enabled = jsonNode["Enabled"].asBool();
				}

			public:
				string Type;
				string Name;
				string Channel;
				bool Enabled;

				virtual ~BaseMaterialCaster()
				{
				}

				virtual void ToJson(Json::Value& jsonNode)
				{
					jsonNode["Type"] = Type;
					jsonNode["Name"] = Name;
					jsonNode["Channel"] = Channel;
					jsonNode["Enabled"] = Enabled;
				}

				static BaseMaterialCaster* ParseJson(const Json::Value& jsonNode);
			};
		}
	}
}