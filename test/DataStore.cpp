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
}
