#ifndef COMMON_HANDLE_HPP
#define COMMON_HANDLE_HPP

#include "common/handle/CHandleObject.hpp"
#include <cstddef>
#include <cstdint>

typedef void* HANDLE;

#define DECLARE_HANDLE(name) \
    struct name##__;         \
    typedef struct name##__* name

DECLARE_HANDLE(HOBJECT);

HOBJECT HandleCreate(CHandleObject* ptr);

void HandleClose(HOBJECT handle);

CHandleObject* HandleDereference(HOBJECT handle);

HOBJECT HandleDuplicate(HOBJECT handle);

#endif
