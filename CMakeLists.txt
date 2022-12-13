cmake_minimum_required(VERSION 3.17)
project(Boggle_Assignment)

# To make Apple happy with catch2
if (APPLE)
    set(CMAKE_CXX_STANDARD 11)
endif()


# link with lld if available for speed
option(ENABLE_LLD "LLD" ON)
if (ENABLE_LLD)
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -fuse-ld=lld -Wl,--version ERROR_QUIET OUTPUT_VARIABLE LLD_VERSION)
    if(LLD_VERSION MATCHES "LLD")
        SET(LLD_AVAILABLE ON)
        MESSAGE(STATUS "lld linker available")
    endif()
endif()

# Precompile catch2 to speed up re-compiles
add_library(catch2_main STATIC unit_tests/catch_main.cpp)
target_include_directories(catch2_main PUBLIC unit_tests/)

add_executable(Basic_Boggle_Solver Basic_Boggle_Solver.cpp Boggle.cpp Dictionary.cpp)
add_executable(Basic_Dictionary Basic_Dictionary.cpp Dictionary.cpp)
add_executable(Dictionary_Tests unit_tests/Dictionary_tests.cpp Dictionary.cpp)
add_executable(Boggle_Tests unit_tests/Boggle_tests.cpp Boggle.cpp Dictionary.cpp)

# Use precompiled catch2 library for all of the executables to speed up recompile times
target_link_libraries(Dictionary_Tests catch2_main)
target_precompile_headers(Dictionary_Tests PRIVATE unit_tests/catch.hpp)

target_link_libraries(Boggle_Tests catch2_main)
target_precompile_headers(Boggle_Tests PRIVATE unit_tests/catch.hpp)


# For Mac
if (APPLE)
    set_property(TARGET Basic_Boggle_Solver PROPERTY CXX_STANDARD 11)
    set_property(TARGET Basic_Dictionary PROPERTY CXX_STANDARD 11)
    set_property(TARGET Dictionary_Tests PROPERTY CXX_STANDARD 11)
    set_property(TARGET Boggle_Tests PROPERTY CXX_STANDARD 11)
endif()