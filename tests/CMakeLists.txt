enable_testing()

find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

add_executable(list_utils_test main-test.cpp)
target_include_directories(list_utils_test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/myLib")

