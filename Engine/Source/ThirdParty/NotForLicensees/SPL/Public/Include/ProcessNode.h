#pragma once

#include <vector>

#include "../json/json.h"

#include "BaseNode.h"
#include "BaseProcessor.h"
#include "BaseMaterialCaster.h"
#include "Enums.h"

namespace Simplygon {
	namespace SPL {
		namespace v80 {

			class  ProcessNode : public BaseNode
			{
			public:
				BaseProcessor* Processor;

				vector<BaseMaterialCaster*> MaterialCaster;
				TangentSpaceMethod DefaultTBNType;

				ProcessNode() : BaseNode()
				{
					Processor = nullptr;
					DefaultTBNType = SG_TANGENTSPACEMETHOD_ORTHONORMAL;
					Type = "ProcessNode";
				}

				ProcessNode(const Json::Value& jsonNode) : BaseNode(jsonNode)
				{
					Type = "ProcessNode";
					
					if (!jsonNode["DefaultTBNType"].isNull()) { DefaultTBNType = Simplygon::SPL::v80::TangentSpaceMethodUtil::Parse(jsonNode["DefaultTBNType"].asString(), SG_TANGENTSPACEMETHOD_ORTHONORMAL); } else { DefaultTBNType = SG_TANGENTSPACEMETHOD_ORTHONORMAL; }

					Processor = BaseProcessor::ParseJson(jsonNode["Processor"]);

					const Json::Value& jsonMaterialCasters = jsonNode["MaterialCaster"];
					for (Json::ValueConstIterator it = jsonMaterialCasters.begin(); it != jsonMaterialCasters.end(); ++it)
					{
						const Json::Value& jsonMaterialCaster = *it;

						BaseMaterialCaster* materialCaster = BaseMaterialCaster::ParseJson(jsonMaterialCaster);
						if (materialCaster != nullptr)
						{
							MaterialCaster.push_back(materialCaster);
						}

					}
				}

				~ProcessNode()
				{
					if (Processor != nullptr) { delete Processor; }

					for (int i = 0; i < MaterialCaster.size(); ++i)
					{
						if (MaterialCaster[i] != nullptr)
						{
							delete MaterialCaster[i];
						}
					}
					MaterialCaster.clear();
				}

				virtual void ToJson(Json::Value& jsonNode)
				{
					BaseNode::ToJson(jsonNode);

					jsonNode["DefaultTBNType"] = TangentSpaceMethodUtil::ToString(DefaultTBNType);

					if (Processor != nullptr)
					{
						Processor->ToJson(jsonNode["Processor"]);
					}

					if (MaterialCaster.size() > 0)
					{
						Json::Value jsonMaterialCasters(Json::arrayValue);
						for (int i = 0; i < MaterialCaster.size(); ++i)
						{
							BaseMaterialCaster* materialCaster = MaterialCaster[i];

							if (materialCaster != nullptr)
							{
								Json::Value jsonNaterialCaster;
								materialCaster->ToJson(jsonNaterialCaster);
								jsonMaterialCasters.append(jsonNaterialCaster);
							}
						}

						jsonNode["MaterialCaster"] = jsonMaterialCasters;
					}
				}
			};
		}
	}
}
