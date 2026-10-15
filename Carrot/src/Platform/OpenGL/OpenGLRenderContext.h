#pragma once

#include "Renderer/RenderContext.h"
#include "Log.h"
#include <stdexcept>

struct GLFWwindow;

namespace Carrot
{
    class OpenGLRenderContext : public RenderContext{
    public:
        OpenGLRenderContext(GLFWwindow* windowHandle):m_Window(windowHandle){}

        virtual void Init() override;
        virtual void SwapBuffer() override;
    private:
        GLFWwindow* m_Window;
    };
}