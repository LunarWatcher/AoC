#include "common/data/CappedBinarySearchList.hpp"
#include <catch2/catch_test_macros.hpp>
#include <cstdint>

TEST_CASE("Basic ordering for n < maxSize", "[CappedBinarySearchList]") {
    common::CappedBinarySearchList<uint64_t> vals(8);

    vals.add(0);
    vals.add(6);

    REQUIRE(vals.items == std::vector<uint64_t> { 0, 6 });
    vals.add(6);
    REQUIRE(vals.items == std::vector<uint64_t> { 0, 6, 6 });
    vals.add(4);
    REQUIRE(vals.items == std::vector<uint64_t> { 0, 4, 6, 6 });
    vals.add(5);
    REQUIRE(vals.items == std::vector<uint64_t> { 0, 4, 5, 6, 6 });
    vals.add(8);
    REQUIRE(vals.items == std::vector<uint64_t> { 0, 4, 5, 6, 6, 8 });
    vals.add(100);
    REQUIRE(vals.items == std::vector<uint64_t> { 0, 4, 5, 6, 6, 8, 100 });
    vals.add(3);
    REQUIRE(vals.items == std::vector<uint64_t> { 0, 3, 4, 5, 6, 6, 8, 100 });
    vals.add(2);
    REQUIRE(vals.items == std::vector<uint64_t> { 0, 2, 3, 4, 5, 6, 6, 8 });
}

TEST_CASE("Advanced ordering at capped list", "[CappedBinarySearchList]") {
    common::CappedBinarySearchList<uint64_t> vals(4);

    for (size_t i = 10; i <= 40; i += 10) {
        vals.add(i);
    }

    REQUIRE(vals.items == std::vector<uint64_t> { 10, 20, 30, 40 });

    SECTION("Smaller") {
        vals.add(0);
        REQUIRE(vals.items == std::vector<uint64_t> { 0, 10, 20, 30 });
    }

    SECTION("Greater") {
        vals.add(50);
        REQUIRE(vals.items == std::vector<uint64_t> { 10, 20, 30, 40 });
    }

}
