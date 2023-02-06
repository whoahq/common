#include "common/BigInteger.hpp"
#include "test/Test.hpp"

TEST_CASE("BigIntegerAdd", "[biginteger]") {
    SECTION("adds 0x10 to 0xFFFFFFFF") {
        auto a = BigIntegerFromInt(0);
        auto b = BigIntegerFromInt(0xFFFFFFFF);
        auto c = BigIntegerFromInt(0x10);

        BigIntegerAdd(a, b, c);

        uint64_t a_;
        BigIntegerToBytes(a, reinterpret_cast<uint8_t*>(&a_), sizeof(a_));

        CHECK(a_ == 0x10000000F);

        BigIntegerFree(a);
        BigIntegerFree(b);
        BigIntegerFree(c);
    }
}

TEST_CASE("BigIntegerAddInt", "[biginteger]") {
    SECTION("adds 0x10 to 0xFFFFFFFF") {
        auto a = BigIntegerFromInt(0);
        auto b = BigIntegerFromInt(0xFFFFFFFF);

        BigIntegerAddInt(a, b, 0x10);

        uint64_t a_;
        BigIntegerToBytes(a, reinterpret_cast<uint8_t*>(&a_), sizeof(a_));

        CHECK(a_ == 0x10000000F);

        BigIntegerFree(a);
        BigIntegerFree(b);
    }
}

TEST_CASE("BigIntegerBitLen", "[biginteger]") {
    SECTION("returns bit length of 0x1234567890") {
        uint64_t bytes = 0x1234567890;
        auto num = BigIntegerFromBytes(reinterpret_cast<uint8_t*>(&bytes), sizeof(bytes));

        CHECK(BigIntegerBitLen(num) == 37);

        BigIntegerFree(num);
    }
}

TEST_CASE("BigIntegerCmp", "[biginteger]") {
    SECTION("compares 10 and 1") {
        auto a = BigIntegerFromInt(10);
        auto b = BigIntegerFromInt(1);

        CHECK(BigIntegerCmp(a, b) == 1);

        BigIntegerFree(a);
        BigIntegerFree(b);
    }
}

TEST_CASE("BigIntegerCmpInt", "[biginteger]") {
    SECTION("compares 10 and 1") {
        auto a = BigIntegerFromInt(10);
        auto b = 1;

        CHECK(BigIntegerCmpInt(a, b) == 1);

        BigIntegerFree(a);
    }
}

TEST_CASE("BigIntegerFromBytes", "[biginteger]") {
    SECTION("creates new biginteger from bytes") {
        uint64_t bytes = 0x1234567890;
        auto num = BigIntegerFromBytes(reinterpret_cast<uint8_t*>(&bytes), sizeof(bytes));

        uint64_t num_;
        BigIntegerToBytes(num, reinterpret_cast<uint8_t*>(&num_), sizeof(num_));

        CHECK(num_ == 0x1234567890);

        BigIntegerFree(num);
    }
}

TEST_CASE("BigIntegerFromInt", "[biginteger]") {
    SECTION("creates new biginteger from integer") {
        auto num = BigIntegerFromInt(4);

        uint32_t num_;
        BigIntegerToBytes(num, reinterpret_cast<uint8_t*>(&num_), sizeof(num_));

        CHECK(num_ == 4);

        BigIntegerFree(num);
    }
}

TEST_CASE("BigIntegerMod", "[biginteger]") {
    SECTION("mods 7 by 4") {
        auto a = BigIntegerFromInt(0);
        auto b = BigIntegerFromInt(7);
        auto c = BigIntegerFromInt(4);

        BigIntegerMod(a, b, c);

        uint32_t a_;
        BigIntegerToBytes(a, reinterpret_cast<uint8_t*>(&a_), sizeof(a_));

        CHECK(a_ == 3);

        BigIntegerFree(a);
        BigIntegerFree(b);
        BigIntegerFree(c);
    }
}

TEST_CASE("BigIntegerModExp", "[biginteger]") {
    SECTION("takes 256 to the 8th power and mods the result by 999") {
        auto a = BigIntegerFromInt(0);
        auto b = BigIntegerFromInt(256);
        auto c = BigIntegerFromInt(8);
        auto d = BigIntegerFromInt(999);

        BigIntegerModExp(a, b, c, d);

        uint32_t a_;
        BigIntegerToBytes(a, reinterpret_cast<uint8_t*>(&a_), sizeof(a_));

        CHECK(a_ == 160);

        BigIntegerFree(a);
        BigIntegerFree(b);
        BigIntegerFree(c);
        BigIntegerFree(d);
    }
}

TEST_CASE("BigIntegerMul", "[biginteger]") {
    SECTION("multiplies 0xFFFFFFFF and 0x100") {
        auto a = BigIntegerFromInt(0);
        auto b = BigIntegerFromInt(0xFFFFFFFF);
        auto c = BigIntegerFromInt(0x100);

        BigIntegerMul(a, b, c);

        uint64_t a_;
        BigIntegerToBytes(a, reinterpret_cast<uint8_t*>(&a_), sizeof(a_));

        CHECK(a_ == 0xFFFFFFFF00);

        BigIntegerFree(a);
        BigIntegerFree(b);
        BigIntegerFree(c);
    }
}

TEST_CASE("BigIntegerSub", "[biginteger]") {
    SECTION("subtracts 0xFF from 0xFFFF") {
        auto a = BigIntegerFromInt(0);
        auto b = BigIntegerFromInt(0xFFFF);
        auto c = BigIntegerFromInt(0xFF);

        BigIntegerSub(a, b, c);

        uint32_t a_;
        BigIntegerToBytes(a, reinterpret_cast<uint8_t*>(&a_), sizeof(a_));

        CHECK(a_ == 0xFF00);

        BigIntegerFree(a);
        BigIntegerFree(b);
        BigIntegerFree(c);
    }
}
