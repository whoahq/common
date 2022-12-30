#include "common/thread/OsTls.hpp"
#include <storm/Thread.hpp>

#if defined(WHOA_SYSTEM_WIN)
#include <windows.h>
#endif

#if defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
#include <storm/Array.hpp>
#include <storm/List.hpp>
#include <pthread.h>
#endif

#if defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
typedef void* TLSData;

struct TLSSlot : public TSLinkedNode<TLSSlot> {
    TSGrowableArray<TLSData> storage;
};

namespace OsTls {
    int8_t s_initialized;
    int32_t s_nextIndex;
    TSList<TLSSlot, TSGetLink<TLSSlot>> s_tlsCleanupList;
    pthread_key_t s_tlsKey;
    SCritSect s_tlsLock;
}
#endif

int32_t OsTlsAlloc() {
#if defined(WHOA_SYSTEM_WIN)
    return TlsAlloc();
#endif

#if defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
    OsTls::s_tlsLock.Enter();

    if (!OsTls::s_initialized) {
        OsTls::s_initialized = 1;
        OsTls::s_nextIndex = 0;
        pthread_key_create(&OsTls::s_tlsKey, nullptr);
    }

    int32_t index = OsTls::s_nextIndex++;

    OsTls:: s_tlsLock.Leave();

    return index;
#endif
}

void* OsTlsGetValue(uint32_t tlsIndex) {
#if defined(WHOA_SYSTEM_WIN)
    return TlsGetValue(tlsIndex);
#endif

#if defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
    if (!OsTls::s_initialized) {
        return nullptr;
    }

    auto slot = static_cast<TLSSlot*>(pthread_getspecific(OsTls::s_tlsKey));

    if (!slot) {
        OsTls::s_tlsLock.Enter();

        slot = OsTls::s_tlsCleanupList.NewNode(1, 1, 0x8);

        OsTls::s_tlsLock.Leave();

        pthread_setspecific(OsTls::s_tlsKey, slot);
    }

    if (slot->storage.Count() > tlsIndex) {
        return slot->storage[tlsIndex];
    } else {
        return nullptr;
    }
#endif
}

int32_t OsTlsSetValue(uint32_t tlsIndex, void* tlsValue) {
#if defined(WHOA_SYSTEM_WIN)
    return TlsSetValue(tlsIndex, tlsValue);
#endif

#if defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
    if (!OsTls::s_initialized) {
        return 0;
    }

    auto slot = static_cast<TLSSlot*>(pthread_getspecific(OsTls::s_tlsKey));

    if (!slot) {
        OsTls::s_tlsLock.Enter();

        slot = OsTls::s_tlsCleanupList.NewNode(1, 1, 0x8);

        OsTls::s_tlsLock.Leave();

        pthread_setspecific(OsTls::s_tlsKey, slot);
    }

    if (slot->storage.Count() > tlsIndex) {
        slot->storage[tlsIndex] = tlsValue;
    } else {
        slot->storage.GrowToFit(tlsIndex, 0);
        slot->storage[tlsIndex] = tlsValue;
    }

    return 1;
#endif
}
