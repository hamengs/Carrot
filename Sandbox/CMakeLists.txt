add_executable(Sandbox src/SandboxApp.cpp)
target_link_libraries(Sandbox PRIVATE Carrot)

if(MSVC)
    target_compile_options(Sandbox PRIVATE /W4)
endif()