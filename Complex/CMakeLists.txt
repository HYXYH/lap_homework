
set(COMPLEX_SOURCE_FILES complex.cpp)
add_library(complex_lib STATIC ${COMPLEX_SOURCE_FILES})

#set(COMPLEX_DEMO_SOURCE_FILES main.cpp )
#add_executable(Complex_Demo ${COMPLEX_DEMO_SOURCE_FILES})
#target_link_libraries(Complex_Demo complex_lib)

set(COMPLEX_TESTS_SOURCE_FILES tests.cpp )
add_executable(Complex_Tests ${COMPLEX_TESTS_SOURCE_FILES})
target_link_libraries(Complex_Tests complex_lib)