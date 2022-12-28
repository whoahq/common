#include "common/objectalloc/ObjAllocGlobals.hpp"

OBJALLOCGLOBALS OBJALLOCGLOBALS::s_globals;
SCritSect OBJALLOCGLOBALS::s_globalsLock;

OBJALLOCGLOBALS* GetObjAllocGlobals() {
    OBJALLOCGLOBALS::s_globalsLock.Enter();

    return &OBJALLOCGLOBALS::s_globals;
}

void ReleaseObjAllocGlobals() {
    OBJALLOCGLOBALS::s_globalsLock.Leave();
}
