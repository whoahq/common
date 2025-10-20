#ifndef COMMON_OBJECTALLOC_C_OBJECT_HEAP_HPP
#define COMMON_OBJECTALLOC_C_OBJECT_HEAP_HPP

#include <cstdint>

class CObjectHeap {
    public:
    // Member variables
    void* m_obj;
    uint32_t* m_indexStack;
    uint32_t m_allocated;

    // Member functions
    CObjectHeap();
    CObjectHeap(const CObjectHeap& source);
    ~CObjectHeap();
    int32_t Allocate(uint32_t objSize, uint32_t heapObjects, const char* heapName);
    int32_t New(uint32_t objSize, uint32_t heapObjects, uint32_t* index, const char* heapName, void** a6, bool zero);
};

#endif
