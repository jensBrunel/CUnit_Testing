include_directories(${CMAKE_SOURCE_DIR}/Stubs)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/Stubs)

add_definitions(-DMODULE_TEST)

add_library(DUT STATIC dut.c dut2.c)

target_link_libraries(DUT Stubs)
