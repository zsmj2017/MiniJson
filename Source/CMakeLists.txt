cmake_minimum_required(VERSION 3.1.0)

project (Json)

# Use C++11
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "C++17 support has been enabled by default.")

file(GLOB_RECURSE SOURCE_FILES *.cpp *.h)

add_library(${PROJECT_NAME} STATIC  ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/src")
