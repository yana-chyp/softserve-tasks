cmake_minimum_required(VERSION 3.13)

find_package(GTest REQUIRED)
message("GTEST_INCLUDE_DIRS = ${GTEST_INCLUDE_DIRS}")

add_library(commonLibrary AnyType.cpp)

add_executable(mainApp main.cpp)
target_link_libraries(mainApp commonLibrary)

add_executable(testRunner testRunner.cpp)
target_link_libraries(testRunner commonLibrary pthread ${GTEST_LIBRARIES})