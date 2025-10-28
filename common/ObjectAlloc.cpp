#include "common/ObjectAlloc.hpp"
#include "common/objectalloc/ObjAllocGlobals.hpp"
#include <storm/Error.hpp>
#include <storm/String.hpp>

int32_t ObjectAlloc(uint32_t heapId, uint32_t* memHandle, void** objectPtr, bool zero) {
    STORM_ASSERT(memHandle);

    *memHandle = 0;

    auto globals = GetObjAllocGlobals();

    STORM_ASSERT(heapId < globals->objects.Count());

    uint32_t index;
    void* object;

    if (globals->objects[heapId].New(&index, &object, zero)) {
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
    STORM_VALIDATE_BEGIN;
    STORM_VALIDATE(objectSize > 0);
    STORM_VALIDATE_END;

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

void ObjectAllocDestroy() {
    // TODO Sub4D2F90();

    auto globals = GetObjAllocGlobals();

    globals->objects.Clear();

    ReleaseObjAllocGlobals();
}

void ObjectFree(uint32_t heapId, uint32_t memHandle) {
    auto globals = GetObjAllocGlobals();

    globals->objects[heapId].Delete(memHandle);

    ReleaseObjAllocGlobals();
}
