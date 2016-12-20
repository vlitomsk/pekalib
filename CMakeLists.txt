cmake_minimum_required(VERSION 2.8.3)
project(pekalib)

set (CMAKE_CXX_STANDARD 11)

enable_testing()
if(GCOV_COVERAGE)
    set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -O0 --coverage -m64" )
    set( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -g -O0 --coverage -lgcov -m64" )
    set( CMAKE_SHARED_LINKER_FLAGS  "${CMAKE_SHARED_LINKER_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage -lgcov -m64" )
endif()

include_directories(include)

add_subdirectory(tests)
add_subdirectory(src)
