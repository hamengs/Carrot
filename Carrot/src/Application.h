#pragma once

#include "Core.h"
#include <memory>
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"

namespace Carrot
{

    class CARROT_API Application
    {
    private:
        /* data */
        bool m_Running = true;
        std::unique_ptr<Window> m_Window;
        LayerStack m_Layers;


        bool OnWindowClose(WindowCloseEvent& e);
    public:
        Application(/* args */);
        virtual ~Application();
        void Run();
        void OnEvent(Event& e);
        void PushLayer(Layer* layer);
        void PushOverLayer(Layer* layer);
    };
    


} // namespace Carrot
