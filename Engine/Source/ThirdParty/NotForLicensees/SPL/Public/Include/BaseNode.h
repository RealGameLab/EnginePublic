#pragma once

#include <string>
#include <vector>

#include "../json/json.h"

using namespace std;

namespace Simplygon {
	namespace SPL {
		namespace v80 {

			class  BaseNode
			{
			protected:
				BaseNode()
				{
				}

				BaseNode(const Json::Value& jsonNode)
				{
					Type = jsonNode["Type"].asString();
					Name = jsonNode["Name"].asString();

					const Json::Value& jsonChildren = jsonNode["Children"];
					for (Json::ValueConstIterator it = jsonChildren.begin(); it != jsonChildren.end(); ++it)
					{
						const Json::Value& jsonChild = *it;
						
						BaseNode* childNode = ParseJson(jsonChild);
						if (childNode != nullptr)
						{
							Children.push_back(childNode);
						}
					}
				}

			public:
				string Type;
				string Name;

				vector<BaseNode*> Children;

				

				virtual ~BaseNode()
				{
					for (int i = 0; i < Children.size(); ++i)
					{
						if (Children[i] != nullptr)
						{
							delete Children[i];
						}
					}
					Children.clear();
				}

				virtual void ToJson(Json::Value& jsonNode)
				{
					jsonNode["Type"] = Type;
					jsonNode["Name"] = Name;
					if (Children.size() > 0)
					{
						Json::Value jsonChildren(Json::arrayValue);
						for (int i = 0; i < Children.size(); ++i)
						{
							BaseNode* childNode = Children[i];

							if (childNode != nullptr)
							{
								Json::Value jsonChild;
								childNode->ToJson(jsonChild);
								jsonChildren.append(jsonChild);
							}
						}

						jsonNode["Children"] = jsonChildren;
					}
				}

				static BaseNode* ParseJson(const Json::Value& jsonNode);
			};
		}
	}
}

