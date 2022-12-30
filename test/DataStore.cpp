#include "common/DataStore.hpp"
#include "test/Test.hpp"

TEST_CASE("CDataStore::CDataStore", "[datastore]") {
    SECTION("constructs new data store") {
        CDataStore msg;
        SUCCEED();
    }
}
