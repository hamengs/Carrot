#pragma once

#include "Renderer/RenderContext.h"

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