#include "common/BigInteger.hpp"
#include <cstring>
#include <storm/Big.hpp>

void BigIntegerAdd(void* a, void* b, void* c) {
    SBigAdd(static_cast<BigData*>(a), static_cast<BigData*>(b), static_cast<BigData*>(c));
}

void BigIntegerAddInt(void* a, void* b, uint32_t c) {
    BigData* c_;
    SBigNew(&c_);
    SBigFromUnsigned(c_, c);

    SBigAdd(static_cast<BigData*>(a), static_cast<BigData*>(b), c_);

    SBigDel(c_);
}

uint32_t BigIntegerBitLen(void* num) {
    uint32_t len;
    SBigBitLen(static_cast<BigData*>(num), &len);

    return len;
}

int32_t BigIntegerCmp(void* a, void* b) {
    return SBigCompare(static_cast<BigData*>(a), static_cast<BigData*>(b));
}

int32_t BigIntegerCmpInt(void* a, uint32_t b) {
    BigData* b_;
    SBigNew(&b_);
    SBigFromUnsigned(b_, b);

    auto result = SBigCompare(static_cast<BigData*>(a), b_);

    SBigDel(b_);

    return result;
}

void BigIntegerFree(void* num) {
    SBigDel(static_cast<BigData*>(num));
}

void* BigIntegerFromBytes(const uint8_t* data, uint32_t bytes) {
    BigData* num;
    SBigNew(&num);
    SBigFromBinary(num, data, bytes);

    return num;
}

void* BigIntegerFromInt(uint32_t val) {
    BigData* num;
    SBigNew(&num);
    SBigFromUnsigned(num, val);

    return num;
}

void BigIntegerMod(void* a, void* b, void* c) {
    SBigMod(static_cast<BigData*>(a), static_cast<BigData*>(b), static_cast<BigData*>(c));
}

void BigIntegerModExp(void* a, void* b, void* c, void* d) {
    SBigPowMod(static_cast<BigData*>(a), static_cast<BigData*>(b), static_cast<BigData*>(c), static_cast<BigData*>(d));
}

void BigIntegerMul(void* a, void* b, void* c) {
    SBigMul(static_cast<BigData*>(a), static_cast<BigData*>(b), static_cast<BigData*>(c));
}

void BigIntegerSub(void* a, void* b, void* c) {
    SBigSub(static_cast<BigData*>(a), static_cast<BigData*>(b), static_cast<BigData*>(c));
}

uint32_t BigIntegerToBytes(void* num, uint8_t* bytes, uint32_t maxBytes) {
    uint32_t copiedBytes;
    SBigToBinaryBuffer(static_cast<BigData*>(num), bytes, maxBytes, &copiedBytes);

    if (maxBytes > copiedBytes) {
        memset(&bytes[copiedBytes], 0, maxBytes - copiedBytes);
    }

    return copiedBytes;
}
