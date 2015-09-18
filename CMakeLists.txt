cmake_minimum_required(VERSION 2.8.7)
project(UnitTesting C)

set(CMAKE_COLOR_MAKEFILE ON)
enable_testing()

# Added for CTest
include(CTest)
# Added for External Projects
include(ExternalProject)

SET(CMAKE_C_FLAGS "-g -O0 -Wall -W --coverage")
SET(CMAKE_CXX_FLAGS "-g -O0 --coverage"
    CACHE STRING "Flags used by the C++ compiler during coverage builds."
    FORCE )
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

################################################################
# Set Module Path
################################################################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

include(CodeCoverage)

SETUP_TARGET_FOR_COVERAGE(coverage UnitTesting coverage)

################################################################
# External: CUNIT
################################################################
ExternalProject_Add(cunit
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CUnit
    CONFIGURE_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/CUnit/ && autoreconf --install && ./configure --prefix=${CMAKE_CURRENT_SOURCE_DIR}/CUnit
    BUILD_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/CUnit/ && make #Build command
    INSTALL_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/CUnit/ && make install 
)

set(CUNIT_LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CUnit/lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/CUnit/CUnit/Headers ${CMAKE_CURRENT_SOURCE_DIR}/DUT ${CMAKE_CURRENT_SOURCE_DIR}/testcases)
LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${CUNIT_LIBRARY_PATH})

add_subdirectory(DUT)
add_subdirectory(testcases)

add_test(UnitTesting ${EXECUTABLE_OUTPUT_PATH}/UnitTesting)

add_executable(UnitTesting main.c)
target_link_libraries(UnitTesting DUT testcases libcunit.a gcov)
