#include "common/data/DisjointSet.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("n = 4", "[DisjointSet]") {
    common::DisjointSet<int64_t> t{ 4 };

    REQUIRE(t.parent.size() == 4);
    REQUIRE(t.sizes.size() == 4);

    for (auto& size : t.sizes) {
        REQUIRE(size == 1);
    }

    SECTION("Chained links") {
        t.link(1, 2);
        REQUIRE(t.sizes.at(1) == 2);

        t.link(2, 3);
        REQUIRE(t.sizes.at(1) == 3);

        t.link(0, 1);
        REQUIRE(t.sizes.at(1) == 4);

        t.link(0, 3);
        REQUIRE(t.sizes.at(1) == 4);
    }
}
