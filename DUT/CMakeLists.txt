include(${PROJECT_SOURCE_DIR}/dut_sources.cmake) 

LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/Stubs)

add_definitions(-DMODULE_TEST)

add_library(DUT STATIC ${DUT_SOURCES})

target_link_libraries(DUT Stubs)
