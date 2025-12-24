#include "common/xml/XMLTree.hpp"
#include "common/xml/Expat.hpp"
#include "common/xml/XMLNode.hpp"

XML_Parser XMLTreeParser;
void* XMLNodeFreeList = nullptr;

void begin_element(void* userData, const XML_Char* name, const XML_Char** atts) {
    auto tree = static_cast<XMLTree*>(userData);

    XMLNode* node;
    if (XMLNodeFreeList) {
        // TODO allocate node off of free list
    } else {
        // TODO allocate node off of node heap
        // XMLNode* node = XMLNode::s_XMLNodeHeap->GetData(0, __FILE__, __LINE__);

        node = new XMLNode(tree->leaf, name);
    }

    auto leaf = tree->leaf;

    if (leaf) {
        XMLNode* child = leaf->m_child;

        if (child) {
            for (; child->m_next; child = child->m_next)
                ;
            child->m_next = node;
        } else {
            leaf->m_child = node;
        }
    } else {
        tree->root = node;
    }

    tree->leaf = node;

    const char** v9 = atts;
    int32_t attCount = 0;

    // Count attributes
    if (*atts) {
        do {
            v9 += 2;
            attCount++;
        } while (*v9);
    }

    node->m_attributes.SetCount(attCount);

    for (int32_t i = 0; i < attCount; i++) {
        node->m_attributes[i].m_name.Copy(atts[i * 2]);
        node->m_attributes[i].m_value.Copy(atts[i * 2 + 1]);
    }
}

void end_element(void* userData, const XML_Char* name) {
    XMLTree* tree = static_cast<XMLTree*>(userData);

    tree->leaf = tree->leaf->m_parent;
}

void handle_body(void* userData, const XML_Char* s, int32_t len) {
    if (len == 0) {
        return;
    }

    XMLTree* tree = static_cast<XMLTree*>(userData);

    XMLNode* node = tree->leaf;

    if (!node->m_body) {
        // Only set initial body if string contains non-whitespace
        char v3;
        int32_t v6 = 0;

        while (1) {
            v3 = s[v6];

            if (v3 != ' ' && v3 != '\t' && v3 != '\r' && v3 != '\n') {
                break;
            }

            v6++;

            if (v6 >= len) {
                return;
            }
        }
    }

    // Allocate / expand if necessary
    char* v7 = static_cast<char*>(SMemReAlloc(node->m_body, node->m_bodyLen + len + 1, __FILE__, __LINE__, 0x0));
    node->m_body = v7;

    // Append character data to end of existing body
    char* v8 = &v7[node->m_bodyLen];
    memcpy(v8, s, len);
    node->m_bodyLen += len;

    // Null terminate the body
    node->m_body[node->m_bodyLen] = '\0';
}

void XMLTree_Free(XMLTree* tree) {
    // TODO
}

XMLNode* XMLTree_GetRoot(XMLTree* tree) {
    return tree->root;
}

XMLTree* XMLTree_Load(const char* data, uint32_t length) {
    XMLTree* tree = static_cast<XMLTree*>(SMemAlloc(sizeof(XMLTree), __FILE__, __LINE__, 0x8));

    if (XMLTreeParser) {
        XML_ParserReset(XMLTreeParser, nullptr);
    } else {
        XMLTreeParser = XML_ParserCreate(nullptr);
    }

    XML_SetElementHandler(XMLTreeParser, begin_element, end_element);
    XML_SetCharacterDataHandler(XMLTreeParser, handle_body);
    XML_SetUserData(XMLTreeParser, tree);

    if (XML_Parse(XMLTreeParser, data, length, 1)) {
        return tree;
    } else {
        if (tree->root) {
            // TODO
            // root->Recycle();
        }

        SMemFree(tree, __FILE__, __LINE__, 0x0);
    }

    return nullptr;
}
