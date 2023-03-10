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

TEST_CASE("SHA1_InterleaveHash", "[sha1]") {
    SECTION("correctly computes interleaved digest of empty string") {
        auto input = "";
        uint8_t digest[SHA1_DIGEST_SIZE * 2];
        uint8_t expected[SHA1_DIGEST_SIZE * 2] = { 0xda, 0xda, 0x39, 0x39, 0xa3, 0xa3, 0xee, 0xee, 0x5e, 0x5e, 0x6b, 0x6b, 0x4b, 0x4b, 0x0d, 0x0d, 0x32, 0x32, 0x55, 0x55, 0xbf, 0xbf, 0xef, 0xef, 0x95, 0x95, 0x60, 0x60, 0x18, 0x18, 0x90, 0x90, 0xaf, 0xaf, 0xd8, 0xd8, 0x07, 0x07, 0x09, 0x09 };

        SHA1_InterleaveHash(digest, reinterpret_cast<const uint8_t*>(input), strlen(input));

        REQUIRE(memcmp(digest, expected, sizeof(digest)) == 0);
    }

    SECTION("correctly computes interleaved digest of 'xyz'") {
        auto input = "xyz";
        uint8_t digest[SHA1_DIGEST_SIZE * 2];
        uint8_t expected[SHA1_DIGEST_SIZE * 2] = { 0x95, 0x39, 0xcb, 0x5d, 0x0b, 0xf8, 0xfd, 0xf7, 0x29, 0xc5, 0x77, 0x1f, 0xc7, 0x00, 0x61, 0x70, 0x29, 0x19, 0x8d, 0xcb, 0x96, 0x30, 0x24, 0x20, 0xe4, 0x1c, 0xb4, 0x49, 0xd4, 0xe8, 0xc7, 0x84, 0x2a, 0xb4, 0x39, 0x6b, 0x97, 0x92, 0x4a, 0xfa };

        SHA1_InterleaveHash(digest, reinterpret_cast<const uint8_t*>(input), strlen(input));

        REQUIRE(memcmp(digest, expected, sizeof(digest)) == 0);
    }

    SECTION("correctly computes interleaved digest of 'foobar'") {
        auto input = "foobar";
        uint8_t digest[SHA1_DIGEST_SIZE * 2];
        uint8_t expected[SHA1_DIGEST_SIZE * 2] = { 0xba, 0xdf, 0x06, 0x40, 0x23, 0x4f, 0xbd, 0x14, 0xc6, 0x5f, 0x7c, 0x1c, 0x26, 0xe8, 0xd2, 0x31, 0x05, 0x06, 0xbb, 0x50, 0x58, 0x88, 0xac, 0x33, 0xc0, 0xf5, 0xaa, 0xe3, 0x9d, 0x03, 0xe6, 0x71, 0x6b, 0xdf, 0xa6, 0x84, 0x0c, 0x40, 0x24, 0xba };

        SHA1_InterleaveHash(digest, reinterpret_cast<const uint8_t*>(input), strlen(input));

        REQUIRE(memcmp(digest, expected, sizeof(digest)) == 0);
    }
}
