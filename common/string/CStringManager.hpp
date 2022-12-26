#ifndef COMMON_STRING_C_STRING_MANAGER_HPP
#define COMMON_STRING_C_STRING_MANAGER_HPP

#include "common/string/CStringMemory.hpp"

#define C_STRING_MANAGER_BUCKETS 521

struct CStringElement;

class CStringManager {
    public:
    // Static variables
    static CStringManager* s_stringManager;

    // Static functions
    static CStringManager* Get();

    // Member variables
    CStringElement* m_buckets[C_STRING_MANAGER_BUCKETS];
    CStringMemory m_memory;

    // Member functions
    CStringManager();
    char* Add(const char* str);
};

#endif
