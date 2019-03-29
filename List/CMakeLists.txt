
set(LIST_SOURCE_FILES List.cpp)
add_library(list_lib STATIC ${LIST_SOURCE_FILES})

#set(LIST_DEMO_SOURCE_FILES main.cpp )
#add_executable(List_Demo ${LIST_DEMO_SOURCE_FILES})
#target_link_libraries(List_Demo list_lib)

set(LIST_TESTS_SOURCE_FILES tests.cpp )
add_executable(List_Tests ${LIST_TESTS_SOURCE_FILES})
target_link_libraries(List_Tests list_lib)

set(LIST_ALLOC_TESTS_SOURCE_FILES allocation_tests.cpp )
add_executable(List_AllocTests ${LIST_ALLOC_TESTS_SOURCE_FILES})
target_link_libraries(List_AllocTests list_lib)