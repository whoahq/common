#include "common/Thread.hpp"
#include "test/Test.hpp"

TEST_CASE("OsTlsAlloc", "[thread]") {
    SECTION("allocates tls index") {
        int32_t tlsIndex = OsTlsAlloc();
        REQUIRE(tlsIndex >= 0);
    }
}

TEST_CASE("OsTlsSetValue", "[thread]") {
    SECTION("sets value in tls index") {
        int32_t tlsIndex = OsTlsAlloc();
        uint32_t tlsValue = 123;
        REQUIRE(OsTlsSetValue(tlsIndex, &tlsValue));
    }
}

TEST_CASE("OsTlsGetValue", "[thread]") {
    SECTION("gets value in tls index") {
        int32_t tlsIndex = OsTlsAlloc();
        uint32_t tlsValue = 456;
        OsTlsSetValue(tlsIndex, &tlsValue);
        REQUIRE(OsTlsGetValue(tlsIndex) == &tlsValue);
    }
}
