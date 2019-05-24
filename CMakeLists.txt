cmake_minimum_required(VERSION 3.1)
project(MyLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CYGWIN)
        set(CMAKE_CXX_EXTENSIONS OFF)
endif()


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-Wall -Werror -Wno-reorder -Wno-sequence-point)
endif()


add_subdirectory(tests)


add_executable(TESTY test.cpp)
target_include_directories(TESTY PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR})
