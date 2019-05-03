

file(GLOB IMGUI_SOURCE_FILES
		${CMAKE_CURRENT_SOURCE_DIR}/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(imgui_lib STATIC ${IMGUI_SOURCE_FILES})
target_link_libraries(imgui_lib glfw glew)