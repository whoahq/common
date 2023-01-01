#ifndef COMMON_MD5_HPP
#define COMMON_MD5_HPP

#include <cstdint>

typedef struct {
    uint32_t state[4];
    uint32_t count[2];
    uint8_t buffer[64];
} MD5_CTX;

void MD5Init(MD5_CTX* context);

void MD5Update(MD5_CTX* context, uint8_t* input, uint32_t inputLen);

void MD5Final(uint8_t digest[16], MD5_CTX* context);

#endif
