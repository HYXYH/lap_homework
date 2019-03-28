
set(BIN_SEARCH_SOURCE_FILES bin_search.cpp)
add_library(bin_search_lib STATIC ${BIN_SEARCH_SOURCE_FILES})
#set_target_properties(bin_search_lib PROPERTIES LINKER_LANGUAGE CXX)


set(DEMO_SOURCE_FILES main.cpp )
add_executable(BinSearch_Demo ${DEMO_SOURCE_FILES})
target_link_libraries(BinSearch_Demo bin_search_lib)

set(TESTS_SOURCE_FILES tests.cpp )
add_executable(BinSearch_Tests ${TESTS_SOURCE_FILES})
target_link_libraries(BinSearch_Tests bin_search_lib)