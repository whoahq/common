#ifndef COMMON_OBJECTALLOC_OBJ_ALLOC_GLOBALS_HPP
#define COMMON_OBJECTALLOC_OBJ_ALLOC_GLOBALS_HPP

#include "common/objectalloc/CObjectHeapList.hpp"
#include <storm/Thread.hpp>

class OBJALLOCGLOBALS {
    public:
    // Static variables
    static OBJALLOCGLOBALS s_globals;
    static SCritSect s_globalsLock;

    // Member variables
    TSGrowableArray<CObjectHeapList> objects;
};

OBJALLOCGLOBALS* GetObjAllocGlobals();

void ReleaseObjAllocGlobals();

#endif
