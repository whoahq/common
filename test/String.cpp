#include "common/String.hpp"
#include "test/Test.hpp"
#include <storm/String.hpp>

TEST_CASE("RCString::Copy", "[string]") {
    SECTION("copies source string") {
        auto str = "foo";
        RCString rcStr;
        rcStr.Copy(str);
        REQUIRE(!SStrCmp(str, rcStr.GetString(), STORM_MAX_STR));
    }
}

TEST_CASE("RCString::GetString", "[string]") {
    SECTION("returns identical pointers for identical source strings") {
        auto str1 = "foo";
        auto str2 = "foo";
        RCString rcStr1;
        rcStr1.Copy(str1);
        RCString rcStr2;
        rcStr2.Copy(str2);
        REQUIRE(rcStr1.GetString() == rcStr2.GetString());
    }

    SECTION("returns different pointers for different source strings") {
        auto str1 = "foo1";
        auto str2 = "foo2";
        RCString rcStr1;
        rcStr1.Copy(str1);
        RCString rcStr2;
        rcStr2.Copy(str2);
        REQUIRE(rcStr1.GetString() != rcStr2.GetString());
    }
}
