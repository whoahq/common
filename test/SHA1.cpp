#include "common/SHA1.hpp"
#include "test/Test.hpp"
#include <cstring>

TEST_CASE("SHA1_Final", "[util]") {
    SECTION("correctly computes digest of empty string") {
        auto input = "";
        uint8_t digest[SHA1_DIGEST_SIZE];
        uint8_t expected[SHA1_DIGEST_SIZE] = { 0xda, 0x39, 0xa3, 0xee, 0x5e, 0x6b, 0x4b, 0x0d, 0x32, 0x55, 0xbf, 0xef, 0x95, 0x60, 0x18, 0x90, 0xaf, 0xd8, 0x07, 0x09 };

        SHA1_CONTEXT ctx;
        SHA1_Init(&ctx);
        SHA1_Update(&ctx, reinterpret_cast<const uint8_t*>(input), strlen(input));
        SHA1_Final(digest, &ctx);

        REQUIRE(memcmp(digest, expected, sizeof(digest)) == 0);
    }

    SECTION("correctly computes digest of 'abc'") {
        auto input = "abc";
        uint8_t digest[SHA1_DIGEST_SIZE];
        uint8_t expected[SHA1_DIGEST_SIZE] = { 0xa9, 0x99, 0x3e, 0x36, 0x47, 0x06, 0x81, 0x6a, 0xba, 0x3e, 0x25, 0x71, 0x78, 0x50, 0xc2, 0x6c, 0x9c, 0xd0, 0xd8, 0x9d };

        SHA1_CONTEXT ctx;
        SHA1_Init(&ctx);
        SHA1_Update(&ctx, reinterpret_cast<const uint8_t*>(input), strlen(input));
        SHA1_Final(digest, &ctx);

        REQUIRE(memcmp(digest, expected, sizeof(digest)) == 0);
    }

    SECTION("correctly computes digest of 'test'") {
        auto input = "test";
        uint8_t digest[SHA1_DIGEST_SIZE];
        uint8_t expected[SHA1_DIGEST_SIZE] = { 0xa9, 0x4a, 0x8f, 0xe5, 0xcc, 0xb1, 0x9b, 0xa6, 0x1c, 0x4c, 0x08, 0x73, 0xd3, 0x91, 0xe9, 0x87, 0x98, 0x2f, 0xbb, 0xd3 };

        SHA1_CONTEXT ctx;
        SHA1_Init(&ctx);
        SHA1_Update(&ctx, reinterpret_cast<const uint8_t*>(input), strlen(input));
        SHA1_Final(digest, &ctx);

        REQUIRE(memcmp(digest, expected, sizeof(digest)) == 0);
    }

    SECTION("correctly computes digest of 0x53 0x51") {
        uint8_t input[] = { 0x53, 0x51 };
        uint8_t digest[SHA1_DIGEST_SIZE];
        uint8_t expected[SHA1_DIGEST_SIZE] = { 0x0c, 0x3d, 0x7a, 0x19, 0xac, 0x7c, 0x62, 0x72, 0x90, 0xbf, 0x03, 0x1e, 0xc3, 0xdf, 0x76, 0x27, 0x7b, 0x0f, 0x7f, 0x75 };

        SHA1_CONTEXT ctx;
        SHA1_Init(&ctx);
        SHA1_Update(&ctx, input, sizeof(input));
        SHA1_Final(digest, &ctx);

        REQUIRE(memcmp(digest, expected, sizeof(digest)) == 0);
    }
}
