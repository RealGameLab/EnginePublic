#pragma once

#include <string>

#include "../json/json.h"

using namespace std;


namespace Simplygon {
	namespace SPL {
		namespace v80 {

			class  BaseProcessor
			{
			protected:
				BaseProcessor()
				{
				}

				BaseProcessor(const Json::Value& jsonNode)
				{
					Type = jsonNode["Type"].asString();
				}

			public:
				string Type;

				

				virtual ~BaseProcessor()
				{
				}

				virtual void ToJson(Json::Value& jsonNode)
				{
					jsonNode["Type"] = Type;
				}

				static BaseProcessor* ParseJson(const Json::Value& jsonNode);
			};
		}
	}
}
