#ifndef COMMON_BIG_INTEGER_HPP
#define COMMON_BIG_INTEGER_HPP

#include <cstdint>

void BigIntegerAdd(void* a, void* b, void* c);

void BigIntegerAddInt(void* a, void* b, uint32_t c);

uint32_t BigIntegerBitLen(void* num);

int32_t BigIntegerCmp(void* a, void* b);

int32_t BigIntegerCmpInt(void* a, uint32_t b);

void BigIntegerFree(void* num);

void* BigIntegerFromBytes(const uint8_t* bytes, uint32_t len);

void* BigIntegerFromInt(uint32_t val);

void BigIntegerMod(void* a, void* b, void* c);

void BigIntegerModExp(void* a, void* b, void* c, void* d);

void BigIntegerMul(void* a, void* b, void* c);

void BigIntegerSub(void* a, void* b, void* c);

uint32_t BigIntegerToBytes(void* num, uint8_t* bytes, uint32_t maxBytes);

#endif
