#include_directories(${CMAKE_CURRENT_SOURCE_DIR} /usr/include/CUnit/ ${CMAKE_SOURCE_DIR}/DUT ${CMAKE_SOURCE_DIR}/Stubs)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/DUT ${CMAKE_SOURCE_DIR}/Stubs)

add_definitions(-DMODULE_TEST)

add_library(testcases STATIC testcases.c )
target_link_libraries(testcases DUT)
