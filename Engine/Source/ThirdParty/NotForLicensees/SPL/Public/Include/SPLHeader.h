#pragma once

#include <string>

#include "../json/json.h"

using namespace std;

namespace Simplygon {
	namespace SPL {
		namespace v80 {

			class  SPLHeader
			{
			public:
				string SPLVersion;
				string ClientName;
				string ClientVersion;
				string SimplygonVersion;

				SPLHeader()
				{
					SPLVersion = "8.0";
				}

				void ParseJson(const Json::Value& jsonNode)
				{
					SPLVersion = jsonNode["Header"]["SPLVersion"].asString();
					ClientName = jsonNode["Header"]["ClientName"].asString();
					ClientVersion = jsonNode["Header"]["ClientVersion"].asString();
					SimplygonVersion = jsonNode["Header"]["SimplygonVersion"].asString();				
				}

				void ToJson(Json::Value& jsonNode)
				{
					jsonNode["SPLVersion"] = SPLVersion;
					jsonNode["ClientName"] = ClientName;
					jsonNode["ClientVersion"] = ClientVersion;
					jsonNode["SimplygonVersion"] = SimplygonVersion;
				}
			};
		}
	}
}
