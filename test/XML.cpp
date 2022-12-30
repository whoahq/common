#include "common/XML.hpp"
#include "test/Test.hpp"
#include <storm/String.hpp>

TEST_CASE("XMLTree_Load", "[xml]") {
    SECTION("loads new tree") {
        auto xml = "<Root><Child1></Child1><Child2></Child2></Root>";
        auto tree = XMLTree_Load(xml, SStrLen(xml));
        REQUIRE(tree);
    }
}
