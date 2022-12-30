#ifndef COMMON_XML_XML_NODE_HPP
#define COMMON_XML_XML_NODE_HPP

#include "common/String.hpp"
#include "common/xml/XMLAttribute.hpp"
#include <cstdint>
#include <storm/Array.hpp>

class XMLNode {
    public:
    // Member variables
    void* m_userData;
    XMLNode* m_parent;
    XMLNode* m_child;
    RCString m_name;
    char* m_body;
    uint32_t m_bodyLen;
    TSGrowableArray<XMLAttribute> m_attributes;
    uint32_t m_offset;
    XMLNode* m_next;

    // Member functions
    XMLNode();
    ~XMLNode();
    const char* GetAttributeByName(const char* name);
    const char* GetBody() const;
    XMLNode* GetChildByName(const char* name);
    const char* GetName();
    void Init(XMLNode* parent, const char* name);
    void SetAttribute(const char* name, const char* value);
};

#endif
