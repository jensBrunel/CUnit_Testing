include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/CUnit/CUnit/Headers ${CMAKE_CURRENT_SOURCE_DIR}/DUT)
LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/DUT)

add_library(testcases SHARED testcases.c)
target_link_libraries(testcases DUT)