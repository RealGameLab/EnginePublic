#pragma once

#include "../json/json.h"

#include "BaseNode.h"

namespace Simplygon {
	namespace SPL {
		namespace v80 {

			class  UnknownNode : public BaseNode
			{
			public:
				UnknownNode() : BaseNode()
				{
					Type = "UnknownNode";
				}

				UnknownNode(const Json::Value& jsonNode) : BaseNode(jsonNode)
				{
					Type = "UnknownNode";
				}
			};
		}
	}
}