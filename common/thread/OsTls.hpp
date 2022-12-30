#ifndef COMMON_THREAD_OS_TLS_HPP
#define COMMON_THREAD_OS_TLS_HPP

#include <cstdint>

int32_t OsTlsAlloc();

void* OsTlsGetValue(uint32_t tlsIndex);

int32_t OsTlsSetValue(uint32_t tlsIndex, void* tlsValue);

#endif
