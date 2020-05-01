cmake_minimum_required(VERSION 3.1.0)

project (MiniJsonTest)

# Use C++11
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "C++17 support has been enabled by default.")

FILE(GLOB_RECURSE TEST_SRC "${CMAKE_SOURCE_DIR}/UnitTest/*.cpp")

add_executable(${PROJECT_NAME} ${TEST_SRC})

target_link_libraries(${PROJECT_NAME} gtest Json)