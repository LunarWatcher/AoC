#include "common/math/Vec.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Normalisation (Vec2d)") {
    SECTION("It should normalise") {
        common::Vec2d unit(1, 1), big(12345, 12345);

        INFO(big.div().x << "," << big.div().y);
        REQUIRE(big.div() == unit.div());
    }
    SECTION("It should deal with signs") {

        common::Vec2d unit(-1, 1), big(-12345, 12345);

        INFO(big.div().x << "," << big.div().y);
        REQUIRE(big.div() == unit.div());

        common::Vec2d a(1, -1);
        REQUIRE(
            unit.div() != a.div()
        );
        REQUIRE(unit.div().x == -a.div().x);
        REQUIRE(unit.div().y == -a.div().y);
    }
}
