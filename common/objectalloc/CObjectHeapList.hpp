#ifndef COMMON_OBJECTALLOC_C_OBJECT_HEAP_LIST_HPP
#define COMMON_OBJECTALLOC_C_OBJECT_HEAP_LIST_HPP

#include "common/objectalloc/CObjectHeap.hpp"
#include <storm/Array.hpp>

class CObjectHeapList {
    public:
    // Member variables
    TSGrowableArray<CObjectHeap> m_heaps;
    uint32_t m_objSize = 0;
    uint32_t m_objsPerBlock = 128;
    uint32_t m_numFullHeaps = 0;
    uint32_t uint1C = 0;
    uint32_t uint20 = 0;
    uint32_t uint24 = 0;
    char m_heapName[80];
    uint32_t uint78 = 0;
    uint32_t uint7C = 0;
    uint32_t uint80 = 0;
    uint8_t char84 = 1;

    // Member functions
    int32_t New(uint32_t* index, void** a3, bool zero);
};

#endif
