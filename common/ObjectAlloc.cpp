#include "common/ObjectAlloc.hpp"
#include "common/objectalloc/ObjAllocGlobals.hpp"
#include <storm/Error.hpp>
#include <storm/String.hpp>

int32_t ObjectAlloc(uint32_t heapId, uint32_t* memHandle, void** objectPtr, bool a4) {
    STORM_ASSERT(memHandle);

    *memHandle = 0;

    auto globals = GetObjAllocGlobals();

    STORM_ASSERT(heapId < globals->objects.Count());

    uint32_t index;
    void* object;

    if (globals->objects[heapId].New(&index, &object, a4)) {
        if (objectPtr) {
            *objectPtr = object;
        }

        ReleaseObjAllocGlobals();

        *memHandle = index;

        return 1;
    }

    ReleaseObjAllocGlobals();

    return 0;
}

uint32_t ObjectAllocAddHeap(uint32_t objectSize, uint32_t objsPerBlock, const char* name, bool a4) {
    STORM_ASSERT(objectSize > 0);

    auto globals = GetObjAllocGlobals();

    uint32_t heapId = globals->objects.Count();
    auto heap = globals->objects.New();

    heap->m_objSize = objectSize;
    heap->m_objsPerBlock = objsPerBlock;
    SStrCopy(heap->m_heapName, name, sizeof(heap->m_heapName));
    heap->char84 = a4;

    ReleaseObjAllocGlobals();

    return heapId;
}
