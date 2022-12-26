#ifndef COMMON_STRING_C_STRING_MANAGER_HPP
#define COMMON_STRING_C_STRING_MANAGER_HPP

#include "common/string/CStringMemory.hpp"

struct CStringElement;

class CStringManager {
    public:
    // Static variables
    static CStringManager* s_stringManager;

    // Static functions
    static CStringManager* Get();

    // Member variables
    CStringElement* m_buckets[521];
    CStringMemory m_memory;

    // Member functions
    CStringManager();
    char* Add(const char* str);
};

#endif
