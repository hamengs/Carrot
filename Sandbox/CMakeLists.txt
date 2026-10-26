add_executable(Sandbox
    src/SandboxApp.cpp
    src/Sandbox2D.cpp
    src/Sandbox2D.h
)

target_link_libraries(Sandbox PRIVATE Carrot)

if(MSVC)
    target_compile_options(Sandbox PRIVATE /W4)
endif()
