#include "common/DataStore.hpp"
#include "test/Test.hpp"
#include <storm/String.hpp>

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

    SECTION("gets string") {
        const char* writeVal = "foobar";
        char readVal[7] = "barfoo";

        CDataStore msg;
        msg.PutString(writeVal);
        msg.Finalize();
        msg.GetString(readVal, sizeof(readVal));

        REQUIRE(SStrCmp(readVal, writeVal, STORM_MAX_STR) == 0);
        REQUIRE(msg.IsRead());
    }

    SECTION("gets string honoring maxchars > 0") {
        const char* writeVal = "foobar";
        char readVal[7] = "bar";

        CDataStore msg;
        msg.PutString(writeVal);
        msg.Finalize();
        msg.GetString(readVal, 3);

        REQUIRE(SStrCmp(readVal, "foo", STORM_MAX_STR) == 0);
        REQUIRE(msg.Tell() == 3);
    }

    SECTION("gets string honoring maxchars of 0") {
        const char* writeVal = "foobar";
        char readVal[7] = "bar";

        CDataStore msg;
        msg.PutString(writeVal);
        msg.Finalize();
        msg.GetString(readVal, 0);

        REQUIRE(msg.Tell() == 0);
    }
}

TEST_CASE("CDataStore::SetSize", "[datastore]") {
    SECTION("sets size") {
        uint8_t writeVal = 8;

        CDataStore msg;
        msg.Put(writeVal);

        CHECK(msg.Size() == 1);

        msg.SetSize(0);

        CHECK(msg.Size() == 0);
    }
}

TEST_CASE("CDataStore::Size", "[datastore]") {
    SECTION("gets size") {
        uint8_t writeVal1 = 8;
        uint16_t writeVal2 = 9;

        CDataStore msg;
        msg.Put(writeVal1);
        msg.Put(writeVal2);

        REQUIRE(msg.Size() == 3);
    }
}

TEST_CASE("CDataStore::Tell", "[datastore]") {
    SECTION("gets bytes read") {
        CDataStore msg;

        uint8_t writeVal1 = 8;
        msg.Put(writeVal1);

        uint16_t writeVal2 = 9;
        msg.Put(writeVal2);

        msg.Finalize();

        CHECK(msg.Tell() == 0);

        uint8_t readVal1;
        msg.Get(readVal1);

        CHECK(msg.Tell() == 1);

        uint16_t readVal2;
        msg.Get(readVal2);

        CHECK(msg.Tell() == 3);
    }
}

TEST_CASE("CDataStoreCache<1024>::CDataStoreCache<1024>", "[datastore]") {
    SECTION("constructs new data store") {
        CDataStoreCache<1024> msg;
        SUCCEED();
    }
}
