cmake_minimum_required(VERSION 3.12)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/releases/download/v1.16.0/googletest-1.16.0.tar.gz
        GIT_TAG v1.14.0
)

FetchContent_MakeAvailable(googletest)

add_executable(
        lib_tests
        time_tests.cpp
        models_tests.cpp
)

target_include_directories(lib_tests PRIVATE
        ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(
        lib_tests
        PRIVATE
        GTest::gtest
        GTest::gtest_main
        finam-api-manager
)

include(GoogleTest)
gtest_discover_tests(lib_tests)