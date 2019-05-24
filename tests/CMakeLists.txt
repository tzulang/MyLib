enable_testing()

option (BUILD_TESTS "build the tests project" ON)
option (BUILD_GTEST_SUB_MODULE "build the tests project" ON)

if (BUILD_TESTS)

    if (BUILD_GTEST_SUB_MODULE)
        message("# BUILDING GTEST FROM SOURCE")
        option(INSTALL_GTEST "" OFF)
        option(BUILD_GMOCK "" OFF)
        add_subdirectory(${CMAKE_SOURCE_DIR}/extern/googletest gtest)
    else()
        #NOT TESTED
        find_package(GTest REQUIRED)
        include_directories(${GTEST_INCLUDE_DIRS})
        link_directories(${GTEST_BOTH_LIBRARIES})
    endif()


    macro (make_test TEST_NAME ) # ${ARGN}=SRC_FILES
        set(SRC_FILES "${ARGN}")
        add_executable(${TEST_NAME} main-test.cpp ${SRC_FILES})
        target_link_libraries(${TEST_NAME} gtest_main gtest)
        target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR})
        add_test(${TEST_NAME} ${TEST_NAME})
    endmacro()

    aux_source_directory(list_utils LIST_UTIL_TEST_SRC)
    make_test(list_utils_test ${LIST_UTIL_TEST_SRC})

    aux_source_directory(math MATH_TEST_SRC)
    make_test(maths_test ${MATH_TEST_SRC})



endif()
