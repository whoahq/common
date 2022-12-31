#include "common/Prop.hpp"
#include "common/Thread.hpp"
#include <storm/Memory.hpp>

namespace Prop {
uint32_t s_tlsIndex;
}

HPROPCONTEXT PropCreateContext() {
    return SMemAlloc(sizeof(void*) * PROPERTIES, __FILE__, __LINE__, 0x8);
}

void* PropGet(PROPERTY id) {
    auto properties = static_cast<void**>(OsTlsGetValue(Prop::s_tlsIndex));

    if (properties) {
        return properties[id];
    } else {
        return nullptr;
    }
}

HPROPCONTEXT PropGetSelectedContext() {
    return OsTlsGetValue(Prop::s_tlsIndex);
}

void PropInitialize() {
    Prop::s_tlsIndex = OsTlsAlloc();
    OsTlsSetValue(Prop::s_tlsIndex, nullptr);
}

void PropSelectContext(HPROPCONTEXT context) {
    OsTlsSetValue(Prop::s_tlsIndex, context);
}

void PropSet(PROPERTY id, void* value) {
    auto properties = static_cast<void**>(OsTlsGetValue(Prop::s_tlsIndex));

    if (properties) {
        properties[id] = value;
    }
}
