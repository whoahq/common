#ifndef COMMON_PROP_HPP
#define COMMON_PROP_HPP

#include "common/prop/Types.hpp"

HPROPCONTEXT PropCreateContext();

void* PropGet(PROPERTY id);

HPROPCONTEXT PropGetSelectedContext();

void PropInitialize();

void PropSelectContext(HPROPCONTEXT context);

void PropSet(PROPERTY id, void* value);

#endif
