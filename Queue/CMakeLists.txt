
set(QUEUE_SOURCE_FILES Queue.cpp)
add_library(queue_lib STATIC ${QUEUE_SOURCE_FILES})

#set(QUEUE_DEMO_SOURCE_FILES main.cpp )
#add_executable(Queue_Demo ${QUEUE_DEMO_SOURCE_FILES})
#target_link_libraries(Queue_Demo queue_lib)

set(QUEUE_TESTS_SOURCE_FILES tests.cpp )
add_executable(Queue_Tests ${QUEUE_TESTS_SOURCE_FILES})
target_link_libraries(Queue_Tests queue_lib)