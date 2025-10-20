#ifndef COMMON_HANDLE_HPP
#define COMMON_HANDLE_HPP

#include "common/handle/CHandleObject.hpp"
#include <storm/Handle.hpp>

DECLARE_STORM_HANDLE(HOBJECT);

HOBJECT HandleCreate(CHandleObject* ptr);

void HandleClose(HOBJECT handle);

CHandleObject* HandleDereference(HOBJECT handle);

HOBJECT HandleDuplicate(HOBJECT handle);

#endif
