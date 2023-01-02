#include "common/mempool/MemPool.hpp"
#include "common/mempool/MemChunk.hpp"

MemPool::MemPool() {
    TSFixedArray<MemChunk*>(this->m_memchunks);
}

void MemPool::Init(size_t blockSize, size_t a2) {
    this->m_unk3 = blockSize * (a2 / blockSize);
    this->m_blockSize = blockSize;
    this->m_unk5 = a2 / blockSize;
}

void* MemPool::MemAlloc() {
    auto count = this->m_memchunks.Count();

    // If chunks already exist, try allocate off of one of them

    for (int32_t i = 0; i < count; i++) {
        auto chunk = this->m_memchunks[i];
        auto mem = chunk->MemAlloc();

        if (mem) {
            return mem;
        }
    }

    // No chunks exist, or all existing chunks are full
    // Create a new chunk and allocate off of it

    this->m_memchunks.SetCount(count + 1);

    void* m = SMemAlloc(sizeof(MemChunk), __FILE__, __LINE__, 0x0);
    MemChunk* chunk = new (m) MemChunk(this->m_blockSize, this->m_unk3);

    this->m_memchunks[count] = chunk;

    return chunk->MemAlloc();
}

int32_t MemPool::MemFree(void* ptr) {
    auto count = this->m_memchunks.Count();

    if (count == 0) {
        return 0;
    }

    int32_t v3 = 0;
    MemChunk* v4;

    while (1) {
        v4 = this->m_memchunks[v3];

        if (v4->Contains(ptr)) {
            break;
        }

        if (++v3 >= count) {
            return 0;
        }
    }

    auto relevantChunk = this->m_memchunks[v3];
    relevantChunk->MemFree(ptr);

    return 1;
}
