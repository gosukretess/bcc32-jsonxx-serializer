#ifndef JsonNode_h_
#define JsonNode_h_
#include <string>
#include <list>
#include "NodeType.h"

namespace RuleEngineWrapper
{
    class JsonNode 
    {
        public:
        std::string Name;
        NodeType Type;
        std::list<JsonNode*> ValueList;
        std::string Value;

        ~JsonNode();
        JsonNode();
        JsonNode(const std::string& name, NodeType type);
        JsonNode(const std::string& name, NodeType type, const std::string& value);
        JsonNode(const std::string& name, NodeType type, std::list<JsonNode*> valueList, const std::string& value);

        void AddDataElement(const std::string& name, const std::string& value);
        void AddNode(JsonNode* node);
        std::string Serialize(NodeType parentType);
        std::string Serialize();
    };
}

#endif
