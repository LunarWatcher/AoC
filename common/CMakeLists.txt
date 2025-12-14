add_library(
    aoc-common
STATIC
    src/common/Runner.cpp
    src/common/fuckingmathbullshit/EqSystem.cpp
)
target_include_directories(
    aoc-common
PUBLIC
    ./src/
)
target_link_libraries(
    aoc-common
PUBLIC
    stc::stc
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(aoc-common PUBLIC stdc++exp)
endif()

add_subdirectory(tests)
