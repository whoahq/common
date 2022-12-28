#include "common/ObjectAlloc.hpp"
#include "test/Test.hpp"

TEST_CASE("ObjectAllocAddHeap", "[objectalloc]") {
    SECTION("creates a new heap and returns a heap id") {
        struct Foo {
            uint32_t field1;
            uint32_t field2;
        };

        auto heapId1 = ObjectAllocAddHeap(sizeof(Foo), 1024, "Foo", true);
        auto heapId2 = ObjectAllocAddHeap(sizeof(Foo), 1024, "Foo", true);

        CHECK(heapId1 == 0);
        CHECK(heapId2 == 1);
    }
}
