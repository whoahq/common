#include "common/Time.hpp"

#if defined(WHOA_SYSTEM_WIN)
#include <windows.h>
#elif defined(WHOA_SYSTEM_MAC)
#include <mach/mach_time.h>
#include <unistd.h>
#elif defined(WHOA_SYSTEM_LINUX) || defined(WHOA_SYSTEM_WEB)
#include <chrono>
#endif

#if defined(WHOA_SYSTEM_LINUX)
#include <unistd.h>
#endif

uint64_t OsGetAsyncTimeMs() {
#if defined(WHOA_SYSTEM_WIN)
    return GetTickCount();

#elif defined(WHOA_SYSTEM_MAC)
    static mach_timebase_info_data_t timebase;

    if (timebase.denom == 0) {
        mach_timebase_info(&timebase);
    }

    uint64_t ticks = mach_absolute_time();

    return ticks * (timebase.numer / timebase.denom) / 1000000;

#elif defined(WHOA_SYSTEM_LINUX) || defined(WHOA_SYSTEM_WEB)
    auto now = std::chrono::steady_clock::now();
    uint64_t ticks = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    return ticks;
#endif
}

uint64_t OsGetAsyncTimeMsPrecise() {
#if defined(WHOA_SYSTEM_WIN)
    // TODO QueryPerformanceCounter implementation
    return OsGetAsyncTimeMs();

#else
    return OsGetAsyncTimeMs();
#endif
}

void OsSleep(uint32_t duration) {
#if defined(WHOA_SYSTEM_WIN)
    Sleep(duration);
#endif

#if defined(WHOA_SYSTEM_MAC) || defined(WHOA_SYSTEM_LINUX)
    usleep(duration);
#endif
}
