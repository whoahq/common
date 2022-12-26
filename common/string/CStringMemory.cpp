#include "common/string/CStringMemory.hpp"
#include <climits>
#include <storm/Memory.hpp>
#include <storm/String.hpp>

void CStringMemory::AllocateBlock(size_t blockSize) {
    // Ensure the block is of a minimum size
    if (blockSize <= 0x10000) {
        blockSize = 0x10000;
    }

    uint32_t index = this->Count();
    this->GrowToFit(index, 0);

    // Allocate the block
    void* block = SMemAlloc(blockSize, __FILE__, __LINE__, 0x0);

    // Store the block in the array
    this->operator[](index) = block;

    this->m_free = reinterpret_cast<uintptr_t>(block);
    this->m_end = reinterpret_cast<uintptr_t>(block) + blockSize;
}

CStringElement* CStringMemory::New(const char* str) {
    size_t strLen = SStrLen(str);

    // Aligned to pointer: sizeof(pointer + string)
    size_t eleSize = (strLen + (sizeof(void*) * 2)) & static_cast<uintptr_t>(-sizeof(void*));

    // Allocation would exceed block end, so allocate a new block
    if (this->m_free + eleSize > this->m_end) {
        this->AllocateBlock(eleSize);
    }

    auto ele = reinterpret_cast<CStringElement*>(this->m_free);

    // Copy the provided string into string memory
    SStrCopy(&ele->str, str, INT_MAX);

    this->m_free += eleSize;

    return ele;
}
