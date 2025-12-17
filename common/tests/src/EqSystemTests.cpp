#include <catch2/catch_test_macros.hpp>

#include <common/hardmath/EqSystem.hpp>

using namespace common;

TEST_CASE("Gaussian elimination") {
    SECTION("Already-reduced systems should not be touched") {
        EqSystem system(2, { 1, 3 });
        system(0, 0) = 1;
        system(1, 1) = 1;

        system.gaussEliminate();
        REQUIRE(system.getMat() == NaiveMatrix<int64_t> {
            { 1, 0, 1 },
            { 0, 1, 3 }
        });

        // TODO: Fix
        // auto res = system.solveForSmallestTotalWithMinConstraints(
        //     0,
        //     1000
        // );

        // REQUIRE(res == std::vector<int64_t>{
        //     1, 3
        // });
    }
}
