#include "common/ObjectAlloc.hpp"
#include "test/Test.hpp"
#include <cstdint>

TEST_CASE("ObjectAllocAddHeap", "[objectalloc]") {
    SECTION("creates new heaps with expected heap ids") {
        struct Foo1 {
            uint32_t field1;
            uint32_t field2;
        };

        struct Foo2 {
            bool field3;
            float field4;
            int32_t field5;
        };

        auto heapId1 = ObjectAllocAddHeap(sizeof(Foo1), 1024, "Foo1", true);
        auto heapId2 = ObjectAllocAddHeap(sizeof(Foo2), 128, "Foo2", true);

        CHECK(heapId1 == 0);
        CHECK(heapId2 == 1);

        ObjectAllocDestroy();
    }
}

TEST_CASE("ObjectAlloc", "[objectalloc]") {
    SECTION("creates new objects from a heap") {
        struct Foo {
            uint32_t field1 = 123;
            uint32_t field2 = 456;
        };

        auto heapId = ObjectAllocAddHeap(sizeof(Foo), 1024, "Foo", true);

        uint32_t foo1Handle;
        void* foo1Mem;
        auto foo1Result = ObjectAlloc(heapId, &foo1Handle, &foo1Mem, true);

        REQUIRE(foo1Result == 1);
        REQUIRE(foo1Handle == 0);

        auto foo1 = new (foo1Mem) Foo();

        uint32_t foo2Handle;
        void* foo2Mem;
        auto foo2Result = ObjectAlloc(heapId, &foo2Handle, &foo2Mem, true);

        REQUIRE(foo2Result == 1);
        REQUIRE(foo2Handle == 1);

        auto foo2 = new (foo2Mem) Foo();
        foo2->field1 = 789;
        foo2->field2 = 101;

        REQUIRE(foo1->field1 == 123);
        REQUIRE(foo1->field2 == 456);
        REQUIRE(foo2->field1 == 789);
        REQUIRE(foo2->field2 == 101);

        ObjectAllocDestroy();
    }
}
