cmake_minimum_required(VERSION 3.20)
project(Carrot LANGUAGES C CXX)

# Keep the application and its DLL together for both Debug and Release.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_library(glad STATIC thrid_party/glad/src/glad.c)
target_include_directories(glad PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/thrid_party/glad/include"
)

add_library(imgui STATIC
    thrid_party/imgui/imgui.cpp
    thrid_party/imgui/imgui_draw.cpp
    thrid_party/imgui/imgui_tables.cpp
    thrid_party/imgui/imgui_widgets.cpp
    thrid_party/imgui/imgui_demo.cpp
    thrid_party/imgui/backends/imgui_impl_glfw.cpp
    thrid_party/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/thrid_party/imgui"
    "${CMAKE_CURRENT_SOURCE_DIR}/thrid_party/imgui/backends"
)

target_link_libraries(imgui PRIVATE glfw)

add_subdirectory(thrid_party/glfw)
add_subdirectory(thrid_party/spdlog)
add_subdirectory(Carrot)
add_subdirectory(Sandbox)

