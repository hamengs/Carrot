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

add_subdirectory(thrid_party/glfw)
add_subdirectory(thrid_party/spdlog)
add_subdirectory(Carrot)
add_subdirectory(Sandbox)

