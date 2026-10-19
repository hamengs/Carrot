add_library(Carrot STATIC
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
    src/Input.h
    src/KeyCode.h
    src/Input.cpp

    src/Events/Events.cpp
    src/Events/Event.h
    src/Events/ApplicationEvent.h
    src/Events/KeyEvent.h
    src/Events/MouseEvent.h


    src/Platform/Windows/WindowsWindow.h
    src/Platform/Windows/WindowsWindow.cpp
    src/Platform/Windows/WindowsInput.h
    src/Platform/Windows/WindowsInput.cpp
    
    src/Platform/OpenGL/OpenGLRenderContext.cpp
    src/Platform/OpenGL/OpenGLBuffer.cpp
    src/Platform/OpenGL/OpenGLVertexArray.cpp
    src/Platform/OpenGL/OpenGLVertexArray.h
    src/Platform/OpenGL/OpenGLRendererAPI.h
    src/Platform/OpenGL/OpenGLRendererAPI.cpp

    src/Renderer/Shader.cpp
    src/Renderer/Shader.h
    src/Renderer/Buffer.cpp
    src/Renderer/Buffer.h
    src/Renderer/VertexArray.cpp
    src/Renderer/VertexArray.h
    src/Renderer/Renderer.h
    src/Renderer/Renderer.cpp
    src/Renderer/OrthographicCamera.h
    src/Renderer/OrthographicCamera.cpp
    src/Renderer/RendererAPI.h
    src/Renderer/RendererAPI.cpp
    src/Renderer/RenderCommand.h
    src/Renderer/RenderCommand.cpp
)

target_precompile_headers(Carrot PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/CarrotPCH.h"
)

target_compile_features(Carrot PUBLIC cxx_std_17)
target_include_directories(Carrot PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/src" 
    "${PROJECT_SOURCE_DIR}/thrid_party/glm"
)

target_sources(Carrot PRIVATE
    src/ImGui/ImGuiLayer.cpp
    src/ImGui/ImGuiLayer.h
)

target_link_libraries(Carrot PUBLIC imgui)

target_link_libraries(Carrot PUBLIC spdlog::spdlog)

target_link_libraries(Carrot PRIVATE glfw glad)

find_package(OpenGL REQUIRED)
target_link_libraries(Carrot PRIVATE OpenGL::GL)

if(MSVC)
    target_compile_options(Carrot PRIVATE /W4)
endif()
