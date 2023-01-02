#ifndef COMMON_MEMPOOL_MEM_CHUNK_HPP
#define COMMON_MEMPOOL_MEM_CHUNK_HPP

#include <cstdlib>

class MemChunk {
    public:
    // Member variables
    void* m_memblocks;
    void* m_free;
    size_t m_unk2;
    size_t m_blockSize;
    size_t m_numBlocks;

    // Member functions
    MemChunk(size_t blockSize, size_t a2);
    bool Contains(void* ptr);
    void* MemAlloc();
    void MemFree(void* ptr);
};

#endif
