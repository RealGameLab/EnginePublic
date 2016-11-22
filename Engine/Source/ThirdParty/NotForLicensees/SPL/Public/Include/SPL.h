#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "../json/json.h"
#include "../json/jsoncpp.cpp"

#include "SPLHeader.h"
#include "BaseNode.h"

namespace Simplygon {
	namespace SPL {
		namespace v80 {
			class  SPL
			{
			public:

				SPLHeader Header;
				BaseNode* ProcessGraph;

				SPL()
				{
					ProcessGraph = nullptr;
				}

				SPL(const Json::Value& jsonNode)
				{
					Header.ParseJson(jsonNode);
					ProcessGraph = BaseNode::ParseJson(jsonNode["ProcessGraph"]);
				}

				~SPL()
				{
					if (ProcessGraph != nullptr)
					{
						delete ProcessGraph;
					}
				}

				void ToJson(Json::Value& jsonNode)
				{
					Header.ToJson(jsonNode["Header"]);
					if (ProcessGraph != nullptr)
					{
						ProcessGraph->ToJson(jsonNode["ProcessGraph"]);
					}
				}

				void Save(std::string filename)
				{
					std::ofstream jsonStream(filename, std::ofstream::binary);

					Json::Value value;
					ToJson(value);

					Json::StreamWriterBuilder builder;
					builder["commentStyle"] = "None";
					builder["indentation"] = "   ";  // or whatever you like
					Json::StreamWriter* writer(builder.newStreamWriter());
					writer->write(value, &jsonStream);
					
					jsonStream.close();
				}

				static SPL* Load(std::string filename)
				{
					Json::Value jsonNode;
					std::ifstream jsonStream(filename, std::ifstream::binary);

					Json::CharReaderBuilder rbuilder;
					std::string errs;
					bool parsingSuccessful = Json::parseFromStream(rbuilder, jsonStream, &jsonNode, &errs);
					if (!parsingSuccessful)
					{
						std::cout << "Failed to parse SPL file\n" << errs;
						return nullptr;
					}
					else
					{
						SPL* spl = new SPL(jsonNode);
						return spl;
					}

					jsonStream.close();
				}

				bool LoadInPlace(std::string filename)
					{
					Json::Value jsonNode;
					std::ifstream jsonStream(filename, std::ifstream::binary);

					Json::CharReaderBuilder rbuilder;
					std::string errs;
					bool parsingSuccessful = Json::parseFromStream(rbuilder, jsonStream, &jsonNode, &errs);
					if (parsingSuccessful)
						{
						Header.ParseJson(jsonNode);
						ProcessGraph = BaseNode::ParseJson(jsonNode["ProcessGraph"]);
						}

					jsonStream.close();

					return parsingSuccessful;
					}
			private:
			};
		}
	}
}