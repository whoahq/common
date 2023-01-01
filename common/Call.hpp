#ifndef COMMON_CALL_HPP
#define COMMON_CALL_HPP

void OsCallDestroy();

void OsCallInitialize(const char* threadName);

void* OsCallInitializeContext(const char* contextName);

void OsCallResetContext(void* contextDataPtr);

void OsCallSetContext(void* contextDataPtr);

#endif
