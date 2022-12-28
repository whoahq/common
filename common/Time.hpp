#ifndef COMMON_TIME_HPP
#define COMMON_TIME_HPP

#include <cstdint>

uint64_t OsGetAsyncTimeMs();

uint64_t OsGetAsyncTimeMsPrecise();

void OsSleep(uint32_t duration);

#endif
