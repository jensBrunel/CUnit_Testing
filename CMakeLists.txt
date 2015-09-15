cmake_minimum_required(VERSION 2.8.7)
project(UnitTesting C)

set(CMAKE_COLOR_MAKEFILE ON)
enable_testing()

# Added for CTest
include(CTest)
# Added for External Projects
include(ExternalProject)

################################################################
# Set Module Path
################################################################
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

################################################################
# External: CUNIT
################################################################
ExternalProject_Add(cunit
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CUnit
    CONFIGURE_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/CUnit/ && autoreconf --install && ./configure 
    BUILD_COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/CUnit/ && make #Build command
    INSTALL_COMMAND ls ./     # skip installation of external project
)
