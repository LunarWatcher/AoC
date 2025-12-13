cmake_minimum_required(VERSION 3.27)
project(AoC)

set (CMAKE_CXX_STANDARD 26)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (NOT WIN32)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

include(FetchContent)
# Linked via common
FetchContent_Declare(stc
    GIT_REPOSITORY https://github.com/LunarWatcher/stc
)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.11.0
)

FetchContent_MakeAvailable(
    stc
    catch2
)

add_subdirectory(common)

add_subdirectory(y2019)
add_subdirectory(y2025)

# The targets move to the latest version (or if I'm going back in time, the version I'm currently working on)
add_custom_target(run
    COMMAND aoc-2025
    DEPENDS aoc-2025
    COMMENT "Run AoC (latest; 2025)")
add_custom_target(test
    COMMAND tests-2025
    DEPENDS tests-2025
    COMMENT "Test AoC (latest; 2025)")
add_custom_target(test-common
    COMMAND tests-common
    DEPENDS tests-common
    COMMENT "Test commons")
# vim:ft=cmake
