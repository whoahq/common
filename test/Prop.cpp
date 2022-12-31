#include "common/Prop.hpp"
#include "test/Test.hpp"

TEST_CASE("PropInitialize", "[prop]") {
    SECTION("initializes prop") {
        PropInitialize();
        SUCCEED();
    }
}
