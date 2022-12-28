#include "common/objectalloc/CObjectHeap.hpp"
#include <cstring>
#include <storm/Memory.hpp>

int32_t CObjectHeap::Allocate(uint32_t objSize, uint32_t heapObjects, const char* heapName) {
    this->m_obj = SMemAlloc(heapObjects * (objSize + sizeof(uint32_t)), heapName, 0, 0x0);

    void* indexStack = static_cast<char*>(this->m_obj) + heapObjects * objSize;
    this->m_indexStack = reinterpret_cast<uint32_t*>(indexStack);

    for (int32_t i = 0; i < heapObjects; i++) {
        this->m_indexStack[i] = i;
    }

    this->m_allocated = 0;

    return this->m_obj != nullptr;
}

int32_t CObjectHeap::New(uint32_t objSize, uint32_t heapObjects, uint32_t* index, const char* heapName, void** a6, bool zero) {
    if (this->m_allocated >= heapObjects) {
        return 0;
    }

    if (!this->m_obj) {
        this->Allocate(objSize, heapObjects, heapName);
    }

    *index = this->m_indexStack[this->m_allocated++];
    void* objPtr = static_cast<char*>(this->m_obj) + objSize * *index;

    if (zero) {
        memset(objPtr, 0, objSize);
    }

    if (a6) {
        *a6 = objPtr;
    }

    return 1;
}
