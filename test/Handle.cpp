#include "common/Handle.hpp"
#include "test/Test.hpp"

class TestHandleObject : public CHandleObject {};

TEST_CASE("HandleCreate", "[handle]") {
    SECTION("returns handle for subclass of CHandleObject") {
        auto testObject = new TestHandleObject();

        auto handle = HandleCreate(testObject);
        CHECK(handle);

        HandleClose(handle);
    }
}
