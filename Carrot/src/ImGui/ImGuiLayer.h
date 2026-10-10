#pragma once

#include "Core.h"
#include "Layer.h"
#include "Window.h"

namespace Carrot
{
    class CARROT_API ImGuiLayer : public Layer{
    public:
        ImGuiLayer(Window* window): m_Window(window){}
        

        void OnAttach() override;
        void OnDetach() override;
        void OnEvent(Event& e) override;
        void OnUpdate() override;

    private:
        Window* m_Window;
        bool    m_ShowDemo = true;

    };
}
