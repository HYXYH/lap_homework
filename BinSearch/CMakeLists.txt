cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(BIN_SEARCH_SOURCE_FILES bin_search.cpp)
add_library(bin_search_lib STATIC ${BIN_SEARCH_SOURCE_FILES})

set(DEMO_SOURCE_FILES main.cpp )
add_executable(Demo ${DEMO_SOURCE_FILES})
target_link_libraries(Demo bin_search_lib)

set(TESTS_SOURCE_FILES tests.cpp )
add_executable(Tests ${TESTS_SOURCE_FILES})
target_link_libraries(Tests bin_search_lib)