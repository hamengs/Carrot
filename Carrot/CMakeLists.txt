add_library(Carrot STATIC
    Carrot.h
    src/Core/Application.cpp
    src/Core/Application.h
    src/Core/CarrotPCH.h
    src/Core/Core.cpp
    src/Core/Core.h
    src/Core/EntryPoint.h
    src/Core/File.h
    src/Core/Input.cpp
    src/Core/Input.h
    src/Core/KeyCode.h
    src/Core/Layer.cpp
    src/Core/Layer.h
    src/Core/LayerStack.cpp
    src/Core/LayerStack.h
    src/Core/Log.cpp
    src/Core/Log.h
    src/Core/Time.cpp
    src/Core/Time.h
    src/Core/Window.cpp
    src/Core/Window.h

    src/Events/ApplicationEvent.h
    src/Events/Event.h
    src/Events/Events.cpp
    src/Events/KeyEvent.h
    src/Events/MouseEvent.h

    src/ImGui/ImGuiLayer.cpp
    src/ImGui/ImGuiLayer.h

    src/Platform/OpenGL/OpenGLBuffer.cpp
    src/Platform/OpenGL/OpenGLBuffer.h
    src/Platform/OpenGL/OpenGLRenderContext.cpp
    src/Platform/OpenGL/OpenGLRenderContext.h
    src/Platform/OpenGL/OpenGLRendererAPI.cpp
    src/Platform/OpenGL/OpenGLRendererAPI.h
    src/Platform/OpenGL/OpenGLShader.cpp
    src/Platform/OpenGL/OpenGLShader.h
    src/Platform/OpenGL/OpenGLTexture2D.cpp
    src/Platform/OpenGL/OpenGLTexture2D.h
    src/Platform/OpenGL/OpenGLVertexArray.cpp
    src/Platform/OpenGL/OpenGLVertexArray.h
    src/Platform/Windows/WindowsInput.cpp
    src/Platform/Windows/WindowsInput.h
    src/Platform/Windows/WindowsTime.cpp
    src/Platform/Windows/WindowsWindow.cpp
    src/Platform/Windows/WindowsWindow.h

    src/Renderer/Buffer.cpp
    src/Renderer/Buffer.h
    src/Renderer/Material.h
    src/Renderer/OrthographicCamera.cpp
    src/Renderer/OrthographicCamera.h
    src/Renderer/OrthographicCameraController.cpp
    src/Renderer/OrthographicCameraController.h
    src/Renderer/RenderCommand.cpp
    src/Renderer/RenderCommand.h
    src/Renderer/RenderContext.h
    src/Renderer/Renderer.cpp
    src/Renderer/Renderer.h
    src/Renderer/Renderer2D.h
    src/Renderer/Renderer2D.cpp
    src/Renderer/RendererAPI.cpp
    src/Renderer/RendererAPI.h
    src/Renderer/Shader.cpp
    src/Renderer/Shader.h
    src/Renderer/Texture.cpp
    src/Renderer/Texture.h
    src/Renderer/VertexArray.cpp
    src/Renderer/VertexArray.h

    src/Profiler/Profiler.h
    src/Profiler/Profiler.cpp
)

target_precompile_headers(Carrot PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Core/CarrotPCH.h"
)

target_compile_features(Carrot PUBLIC cxx_std_17)
target_include_directories(Carrot PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/src" 
    "${PROJECT_SOURCE_DIR}/thrid_party/glm"
)

target_link_libraries(Carrot PUBLIC imgui)

target_link_libraries(Carrot PUBLIC spdlog::spdlog)

target_link_libraries(Carrot PRIVATE stb_image)

target_link_libraries(Carrot PRIVATE glfw glad)

find_package(OpenGL REQUIRED)
target_link_libraries(Carrot PRIVATE OpenGL::GL)

if(MSVC)
    target_compile_options(Carrot PRIVATE /W4)
endif()
