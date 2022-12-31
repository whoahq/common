#include "common/Array.hpp"
#include "test/Test.hpp"

struct PrioritizedEntry {
    const char* name;
    uint32_t priority;
};

TEST_CASE("CSimpleSortedArray::CSimpleSortedArray", "[array]") {
    SECTION("constructs new sorted array") {
        CSimpleSortedArray<PrioritizedEntry> array;
        REQUIRE(array.Count() == 0);
    }
}

TEST_CASE("CSimpleSortedArray::Insert", "[array]") {
    SECTION("sorts entries as new elements are inserted") {
        CSimpleSortedArray<PrioritizedEntry*> array;

        PrioritizedEntry* entry1 = new PrioritizedEntry();
        entry1->name = "Entry1";
        entry1->priority = 1;

        PrioritizedEntry* entry2 = new PrioritizedEntry();
        entry2->name = "Entry2";
        entry2->priority = 10;

        PrioritizedEntry* entry3 = new PrioritizedEntry();
        entry3->name = "Entry3";
        entry3->priority = 100;

        array.Insert(entry2);

        CHECK(array[0]->priority == entry2->priority);
        CHECK(array.Count() == 1);

        array.Insert(entry1);

        CHECK(array[0]->priority == entry2->priority);
        CHECK(array[1]->priority == entry1->priority);
        CHECK(array.Count() == 2);

        array.Insert(entry3);

        CHECK(array[0]->priority == entry3->priority);
        CHECK(array[1]->priority == entry2->priority);
        CHECK(array[2]->priority == entry1->priority);
        CHECK(array.Count() == 3);
    }
}

TEST_CASE("CSimpleSortedArray::Remove", "[array]") {
    SECTION("consolidates entries as elements are removed") {
        CSimpleSortedArray<PrioritizedEntry*> array;

        PrioritizedEntry* entry1 = new PrioritizedEntry();
        entry1->name = "Entry1";
        entry1->priority = 1;

        PrioritizedEntry* entry2 = new PrioritizedEntry();
        entry2->name = "Entry2";
        entry2->priority = 10;

        PrioritizedEntry* entry3 = new PrioritizedEntry();
        entry3->name = "Entry3";
        entry3->priority = 100;

        array.Insert(entry1);
        array.Insert(entry2);
        array.Insert(entry3);

        CHECK(array[0]->priority == entry3->priority);
        CHECK(array[1]->priority == entry2->priority);
        CHECK(array[2]->priority == entry1->priority);
        CHECK(array.Count() == 3);

        array.Remove(1);

        CHECK(array[0]->priority == entry3->priority);
        CHECK(array[1]->priority == entry1->priority);
        CHECK(array.Count() == 2);

        array.Remove(0);

        CHECK(array[0]->priority == entry1->priority);
        CHECK(array.Count() == 1);
    }
}
