#pragma once

#include "Input.h"
#include "Window.h"

namespace Carrot{
    class WindowsInput : public Input{
    public:
        explicit WindowsInput(Window& window): m_Window(window){

        }
    protected:

        std::pair<float, float> GetMousePositionImple() override;
    private:
        Window& m_Window;
    };
}

