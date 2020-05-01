cmake_minimum_required(VERSION 3.1.0)

project(MiniJson)
message("current build type is ${CMAKE_BUILD_TYPE}")

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "C++17 support has been enabled by default.")

add_subdirectory("Source")

if (ENABLE_MINIJSON_TEST)
    add_subdirectory("gtest")
    add_subdirectory("UnitTest")
endif()
