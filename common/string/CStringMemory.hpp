#ifndef COMMON_STRING_C_STRING_MEMORY_HPP
#define COMMON_STRING_C_STRING_MEMORY_HPP

#include <storm/Array.hpp>

struct CStringElement {
    CStringElement* next;
    char str;
};

class CStringMemory : public TSGrowableArray<void*> {
    public:
    // Member variables
    uintptr_t m_free;
    uintptr_t m_end;

    // Member functions
    void AllocateBlock(size_t blockSize);
    CStringElement* New(const char* str);
};

#endif
