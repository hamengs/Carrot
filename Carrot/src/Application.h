#pragma once

#include "Core.h"
#include <memory>
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Renderer/OrthographicCamera.h"
#include "Core/Time.h"
#include "Renderer/Renderer.h"

namespace Carrot
{
    class ImGuiLayer;
    class Shader;
    class VertexArray;

    class CARROT_API Application
    {
    private:
        /* data */
        bool m_Running = true;
        bool m_IsMinimize = false;
        Scope<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer = nullptr;
        LayerStack m_Layers;
        bool OnWindowClose(WindowCloseEvent& e);



    public:
        Application(/* args */);
        virtual ~Application();
        void Run();
        void OnEvent(Event& e);
        void PushLayer(Layer* layer);
        void PushOverLayer(Layer* layer);
        Window& GetWindow() { return *m_Window; }
        bool OnWindowResize(WindowResizeEvent& e);
    };
    


} // namespace Carrot
