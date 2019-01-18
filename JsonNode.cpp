#include "JsonNode.h"
#include <sstream>

namespace RuleEngineWrapper
{
    JsonNode::~JsonNode()
    {
        while(!ValueList.empty()) delete ValueList.back(), ValueList.pop_back();
    }

    JsonNode::JsonNode(const std::string& name, NodeType type)
    {
        Name = name;
        Type = type;
    }

    JsonNode::JsonNode(const std::string& name, NodeType type, std::list<JsonNode*> valueList, const std::string& value)
    {
        Name = name;
        Type = type;
        ValueList = valueList;
        Value = value;
    }

    JsonNode::JsonNode(const std::string& name, NodeType type, const std::string& value)
    {
        Name = name;
        Type = type;
        Value = value;
    }

    void JsonNode::AddDataElement(const std::string& name, const std::string& value)
    {
        JsonNode* node = new JsonNode(name, Data, value);
        ValueList.push_back(node);
    }

    void JsonNode::AddNode(JsonNode* node)
    {
        ValueList.push_back(node);
    }

    std::string JsonNode::Serialize()
    {
        return Serialize(Object);
    }

    std::string JsonNode::Serialize(NodeType parentType)
    {
        std::stringstream ss;

        // Element name - check if parent parentType was array
        if (parentType != Array)
        {
            ss << "\"" << Name << "\":";
        }

        // Opening brackets
        switch (Type)
        {
            case Object:
                ss  << "{";
                break;
            case Array:
                ss << "[";
                break;
        }

        if (!ValueList.empty())
        {
            std::list<JsonNode*>::iterator it;
            for (it = ValueList.begin(); it != ValueList.end(); ++it)
            {
                ss << (*it)->Serialize(Type);
                if (ValueList.back() != *it) ss << ",";
            }
        }

        // print final value (only strings are supported)
        if (Type == Data) ss << "\"" << Value << "\"";

        // Closing brackets
        switch (Type)
        {
            case Object:
                ss << "}";
                break;
            case Array:
                ss << "]";
                break;
        }
        return ss.str();
    }
}