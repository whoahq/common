#ifndef COMMON_MEMPOOL_MEM_POOL_HPP
#define COMMON_MEMPOOL_MEM_POOL_HPP

#include <cstdint>
#include <cstdlib>
#include <storm/Array.hpp>

class MemChunk;

class MemPool {
    public:
    // Member variables
    TSFixedArray<MemChunk*> m_memchunks;
    size_t m_unk3;
    size_t m_blockSize;
    size_t m_unk5;

    // Member functions
    MemPool();
    void Init(size_t blockSize, size_t a2);
    void* MemAlloc();
    int32_t MemFree(void* ptr);
};

#endif
