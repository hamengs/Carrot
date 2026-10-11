#pragma once

#include "Core.h"
#include "Layer.h"
#include "Window.h"

namespace Carrot
{
    class CARROT_API ImGuiLayer : public Layer{
    public:
        ImGuiLayer(Window* window): m_Window(window){}
        

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnEvent(Event& e) override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();
    private:
        Window* m_Window;
        bool    m_ShowDemo = true;

    };
}
