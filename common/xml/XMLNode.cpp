#include "common/xml/XMLNode.hpp"
#include <storm/String.hpp>

XMLNode::XMLNode() {
    // TODO
}

XMLNode::~XMLNode() {
    // TODO
}

const char* XMLNode::GetAttributeByName(const char* name) const {
    for (int32_t i = 0; i < this->m_attributes.Count(); i++) {
        auto& attribute = this->m_attributes[i];

        if (!SStrCmpI(attribute.m_name.GetString(), name, STORM_MAX_STR)) {
            return attribute.m_value.GetString();
        }
    }

    return nullptr;
}

const char* XMLNode::GetBody() const {
    return this->m_body;
}

const XMLNode* XMLNode::GetChild() const {
    return this->m_child;
}

const XMLNode* XMLNode::GetChildByName(const char* name) const {
    auto child = this->m_child;

    if (!child) {
        return nullptr;
    }

    while (SStrCmpI(child->m_name.GetString(), name, STORM_MAX_STR)) {
        child = child->m_next;

        if (!child) {
            return nullptr;
        }
    }

    return child;
}

const char* XMLNode::GetName() const {
    return this->m_name.GetString();
}

const XMLNode* XMLNode::GetSibling() const {
    return this->m_next;
}

void XMLNode::Init(XMLNode* parent, const char* name) {
    RCString(this->m_name);
    TSGrowableArray<XMLAttribute>(this->m_attributes);
    this->m_parent = parent;
    this->m_child = nullptr;
    this->m_name.Copy(name);
    this->m_body = nullptr;
    this->m_bodyLen = 0;

    if (this->m_parent && this->m_parent->m_body) {
        this->m_next = nullptr;
        this->m_userData = nullptr;
        this->m_offset = this->m_parent->m_bodyLen;
    } else {
        this->m_offset = 0;
        this->m_next = nullptr;
        this->m_userData = nullptr;
    }
}

void XMLNode::SetAttribute(const char* name, const char* value) {
    auto attributeCount = this->m_attributes.Count();

    for (int32_t i = 0; i < attributeCount; i++) {
        if (!SStrCmpI(name, this->m_attributes[i].m_name.GetString(), STORM_MAX_STR)) {
            this->m_attributes[i].m_value.Copy(value);
            return;
        }
    }

    this->m_attributes.SetCount(attributeCount + 1);
    this->m_attributes[attributeCount].m_name.Copy(name);
    this->m_attributes[attributeCount].m_value.Copy(value);
}
