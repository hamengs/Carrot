#include "WindowsInput.h"
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace Carrot
{
    Input* Input::s_Instance = nullptr;

    void Input::Init(Window& window){
        if (s_Instance)
            throw std::logic_error("Input is already initialized. ShutDown before initializing again.");
        s_Instance = new WindowsInput(window);
    }

    void Input::ShutDown(){
        delete s_Instance;
        s_Instance = nullptr;
    }

std::pair<float, float> WindowsInput::GetMousePositionImple(){
        auto* window = static_cast<GLFWwindow*>(m_Window.GetNativeWindow());
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return {static_cast<float>(x), static_cast<float>(y)};
    }
} // namespace Carrot

