#include "common/DataStore.hpp"
#include "test/Test.hpp"

TEST_CASE("CDataStore::CDataStore", "[datastore]") {
    SECTION("constructs new data store") {
        CDataStore msg;
        SUCCEED();
    }
}

TEST_CASE("CDataStore::Get", "[datastore]") {
    SECTION("gets uint8_t") {
        uint8_t writeVal = 8;
        uint8_t readVal = -1;

        CDataStore msg;
        msg.Put(writeVal);
        msg.Finalize();
        msg.Get(readVal);

        REQUIRE(readVal == writeVal);
    }

    SECTION("gets uint16_t") {
        uint16_t writeVal = 0x1234;
        uint16_t readVal = -1;

        CDataStore msg;
        msg.Put(writeVal);
        msg.Finalize();
        msg.Get(readVal);

        REQUIRE(readVal == writeVal);
    }

    SECTION("gets uint32_t") {
        uint32_t writeVal = 0x12345678;
        uint32_t readVal = 0x12345678;

        CDataStore msg;
        msg.Put(writeVal);
        msg.Finalize();
        msg.Get(readVal);

        REQUIRE(readVal == writeVal);
    }

    SECTION("gets uint64_t") {
        uint64_t writeVal = 0x1122334455667788;
        uint64_t readVal = 0x1122334455667788;

        CDataStore msg;
        msg.Put(writeVal);
        msg.Finalize();
        msg.Get(readVal);

        REQUIRE(readVal == writeVal);
    }

    SECTION("gets float") {
        float writeVal = 1.5f;
        float readVal = -1.0f;

        CDataStore msg;
        msg.Put(writeVal);
        msg.Finalize();
        msg.Get(readVal);

        REQUIRE(readVal == writeVal);
    }
}
