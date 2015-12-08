cmake_minimum_required(VERSION 2.8.7)
project(UnitTesting C)

set(CMAKE_COLOR_MAKEFILE ON)
enable_testing()

# Added for CTest
include(CTest)
# Added for External Projects
include(ExternalProject)

add_definitions(-DMODULE_TEST)

SET(CMAKE_C_FLAGS "-g -Wall -W -pedantic --coverage")
SET(CMAKE_CXX_FLAGS "-g --coverage"
    CACHE STRING "Flags used by the C++ compiler during coverage builds."
    FORCE )
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

################################################################
# Set Module Path
################################################################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

include(CodeCoverage)
include(FindLint)
include(CorrectWindowsPaths)

SETUP_TARGET_FOR_COVERAGE(coverage UnitTesting coverage)

SET (SRCS ${CMAKE_CURRENT_SOURCE_DIR}/DUT/sl_rom_test_configuration.c
 ${CMAKE_CURRENT_SOURCE_DIR}/DUT/sl_callback.c
 ${CMAKE_CURRENT_SOURCE_DIR}/DUT/sl_lockstep_test.c
 ${CMAKE_CURRENT_SOURCE_DIR}/DUT/sl_mpu_test.c
 ${CMAKE_CURRENT_SOURCE_DIR}/DUT/sl_mpu_test_configuration.c
 ${CMAKE_CURRENT_SOURCE_DIR}/DUT/sl_register_safeguard.c
 ${CMAKE_CURRENT_SOURCE_DIR}/DUT/sl_register_safeguard_configuration.c
 ${CMAKE_CURRENT_SOURCE_DIR}/DUT/sl_rom_test.c
 ${CMAKE_CURRENT_SOURCE_DIR}/DUT/sl_scheduler.c
 ${CMAKE_CURRENT_SOURCE_DIR}/DUT/sl_time_safeguard.c
)

lint_check_sources(lint gcc g++ ${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS} ${SRCS})

################################################################
# External: CUNIT
################################################################
ExternalProject_Add(cunit
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CUnit
    CONFIGURE_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/CUnit/ && autoreconf --install && ./configure
    BUILD_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/CUnit/ && make #Build command
    INSTALL_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/CUnit/ && make install 
)

################################################################
# External: lcov
################################################################
ExternalProject_Add(lcov
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lcov
    CONFIGURE_COMMAND cd .
    BUILD_COMMAND cd .
    INSTALL_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/lcov/ && make install
)

set(CUNIT_LIBRARY_PATH /usr/local/lib/)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} /usr/local/include/CUnit/ ${CMAKE_CURRENT_SOURCE_DIR}/DUT ${CMAKE_CURRENT_SOURCE_DIR}/testcases)
LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${CUNIT_LIBRARY_PATH})

add_subdirectory(Stubs)
add_subdirectory(DUT)
add_subdirectory(testcases)

add_test(UnitTesting ${EXECUTABLE_OUTPUT_PATH}/UnitTesting)

add_executable(UnitTesting main.c)
add_dependencies(UnitTesting locv cunit Stubs DUT testcases lint)

target_link_libraries(UnitTesting Stubs DUT testcases libcunit.a gcov)
