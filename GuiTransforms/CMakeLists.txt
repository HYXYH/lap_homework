find_package(OpenGL REQUIRED)

set(GUI_TRANSFORMS_SOURCE_FILES main.cpp )
add_executable(GuiTransforms ${GUI_TRANSFORMS_SOURCE_FILES})
target_link_libraries(GuiTransforms imgui_lib "/System/Library/Frameworks/OpenGL.framework")
target_include_directories(GuiTransforms PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../external/imgui/)