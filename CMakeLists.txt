cmake_minimum_required(VERSION 3.20)
project(Carrot LANGUAGES CXX)

# Keep the application and its DLL together for both Debug and Release.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(Carrot)
add_subdirectory(Sandbox)

