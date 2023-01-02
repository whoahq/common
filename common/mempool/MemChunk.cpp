#include "common/mempool/MemChunk.hpp"
#include <storm/Memory.hpp>

struct MemBlock {
    void* next;
};

MemChunk::MemChunk(size_t blockSize, size_t a2) {
    this->m_blockSize = blockSize;
    this->m_numBlocks = a2 / blockSize;

    size_t v4 = blockSize * (a2 / blockSize);
    this->m_unk2 = v4;

    void* data = SMemAlloc(v4, __FILE__, __LINE__, 0x0);
    this->m_memblocks = data;
    this->m_free = data;

    auto bytes = static_cast<char*>(data);
    auto last = &bytes[this->m_unk2 - this->m_blockSize];
    MemBlock* block;

    while ((uintptr_t)bytes < (uintptr_t)last) {
        block = reinterpret_cast<MemBlock*>(bytes);

        // Drop a pointer to the next block
        block->next = &bytes[this->m_blockSize];

        // Move to the next block
        bytes += this->m_blockSize;
    }

    // Drop null pointer in last block
    block = reinterpret_cast<MemBlock*>(bytes);
    block->next = nullptr;
}

bool MemChunk::Contains(void* ptr) {
    return (uintptr_t)ptr >= (uintptr_t)this->m_memblocks && (uintptr_t)ptr < (uintptr_t)this->m_memblocks + this->m_unk2;
}

void* MemChunk::MemAlloc() {
    auto block = reinterpret_cast<MemBlock*>(this->m_free);

    if (block) {
        this->m_free = block->next;
        this->m_numBlocks--;
        return static_cast<void*>(block);
    } else {
        return nullptr;
    }
}

void MemChunk::MemFree(void* ptr) {
    auto block = reinterpret_cast<MemBlock*>(ptr);

    block->next = this->m_free;
    this->m_free = block;

    this->m_numBlocks++;
}
