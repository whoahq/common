#include "common/Handle.hpp"
#include "common/handle/CHandleObject.hpp"
#include <storm/Error.hpp>

HOBJECT HandleCreate(CHandleObject* ptr) {
    STORM_ASSERT(ptr);
    STORM_VALIDATE(ptr, ERROR_INVALID_PARAMETER, nullptr);

    ptr->m_refcount++;
    return reinterpret_cast<HOBJECT>(ptr);
}

void HandleClose(HOBJECT handle) {
    CHandleObject* ptr = HandleDereference(handle);

    STORM_ASSERT(ptr->m_refcount > 0);

    ptr->m_refcount--;

    if (ptr->m_refcount == 0) {
        delete ptr;
    }
}

CHandleObject* HandleDereference(HOBJECT handle) {
    return reinterpret_cast<CHandleObject*>(handle);
}

HOBJECT HandleDuplicate(HOBJECT handle) {
    if (!handle) {
        return nullptr;
    }

    HandleDereference(handle)->m_refcount++;
    return handle;
}
