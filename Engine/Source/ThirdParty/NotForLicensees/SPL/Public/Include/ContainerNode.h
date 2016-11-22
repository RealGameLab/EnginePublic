#pragma once

#include "../json/json.h"

#include "BaseNode.h"

namespace Simplygon {
	namespace SPL {
		namespace v80 {

			class  ContainerNode : public BaseNode
			{
			public:
				ContainerNode() : BaseNode()
				{
					Type = "ContainerNode";
				}

				ContainerNode(const Json::Value& jsonNode) : BaseNode(jsonNode)
				{
					Type = "ContainerNode";
				}
			};
		}
	}
}