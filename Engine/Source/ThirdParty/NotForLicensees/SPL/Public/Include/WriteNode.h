#pragma once

#include <string>

#include "../json/json.h"

#include "BaseNode.h"

using namespace std;

namespace Simplygon {
	namespace SPL {
		namespace v80 {

			class WriteNode : public BaseNode
			{
			public:
				string Format;

				WriteNode() : BaseNode()
				{
					Type = "WriteNode";
				}

				WriteNode(const Json::Value& jsonNode) : BaseNode(jsonNode)
				{
					Type = "WriteNode";

					if (!jsonNode["Format"].isNull()) { Format = jsonNode["Format"].asString(); }
				}

				virtual void ToJson(Json::Value& jsonNode)
				{
					BaseNode::ToJson(jsonNode);

					jsonNode["Format"] = Format;
				}
			};
		}
	}
}