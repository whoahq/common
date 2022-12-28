#include "common/objectalloc/CObjectHeapList.hpp"
#include "storm/Error.hpp"

int32_t CObjectHeapList::New(uint32_t* index, void** a3, bool zero) {
    CObjectHeap* heap = nullptr;

    if (this->uint24 < this->m_heaps.Count()) {
        heap = &this->m_heaps[this->uint24];
    }

    if (!heap || heap->m_allocated == this->m_objsPerBlock || !heap->m_obj) {
        if (this->m_heaps.Count() == this->m_numFullHeaps) {
            this->uint24 = this->m_heaps.Count();

            heap = this->m_heaps.New();

            if (!heap->Allocate(this->m_objSize, this->m_objsPerBlock, this->m_heapName)) {
                return 0;
            }
        } else {
            // TODO
            // Find available heap
            STORM_ASSERT(false);
        }
    }

    if (!heap->New(this->m_objSize, this->m_objsPerBlock, index, this->m_heapName, a3, zero)) {
        return 0;
    }

    *index += this->uint24 * this->m_objsPerBlock;

    if (heap->m_allocated == this->m_objsPerBlock) {
        this->m_numFullHeaps++;
    }

    return 1;
}
