cmake_minimum_required(VERSION 2.8.3)
project(pekalib)

add_subdirectory(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable( utest utest.cpp )

target_link_libraries (utest gtest gtest_main)
add_test( utest utest )
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS utest)
