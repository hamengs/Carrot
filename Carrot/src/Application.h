#pragma once

#include "Core.h"
#include <memory>
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Platform/OpenGL/OpenGLRenderContext.h"

namespace Carrot
{

    class CARROT_API Application
    {
    private:
        /* data */
        bool m_Running = true;
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer = nullptr;
        LayerStack m_Layers;

        bool OnWindowClose(WindowCloseEvent& e);

        std::shared_ptr<VertexArray> m_VAO;
        std::shared_ptr<Shader> m_Shader;
    public:
        Application(/* args */);
        virtual ~Application();
        void Run();
        void OnEvent(Event& e);
        void PushLayer(Layer* layer);
        void PushOverLayer(Layer* layer);
        Window& GetWindow() { return *m_Window; }
    };
    


} // namespace Carrot
