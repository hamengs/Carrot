add_library(Carrot SHARED
    src/Application.cpp
    src/Application.h
    src/Log.cpp
    src/Log.h
    src/Window.h
    src/Window.cpp
    src/Layer.h
    src/Layer.cpp
    src/LayerStack.h
    src/LayerStack.cpp

    src/Events/Events.cpp
    src/Events/Event.h
    src/Events/ApplicationEvent.h
    src/Events/KeyEvent.h
    src/Events/MouseEvent.h


    src/Platform/Windows/WindowsWindow.h
    src/Platform/Windows/WindowsWindow.cpp
)

target_precompile_headers(Carrot PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/CarrotPCH.h"
)

target_compile_features(Carrot PUBLIC cxx_std_17)
target_include_directories(Carrot PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_compile_definitions(Carrot PRIVATE CARROT_BUILD_DLL)
target_link_libraries(Carrot PUBLIC spdlog::spdlog)

target_link_libraries(Carrot PRIVATE glfw glad)

find_package(OpenGL REQUIRED)
target_link_libraries(Carrot PRIVATE OpenGL::GL)