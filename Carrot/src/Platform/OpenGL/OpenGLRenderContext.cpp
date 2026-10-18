#include "OpenGLRenderContext.h"
#include <GLFW/glfw3.h>

namespace Carrot
{
    //设置opengl的上下文来自哪个窗口
    void OpenGLRenderContext::Init(){
        glfwMakeContextCurrent(m_Window);
    }
    
    //交换这个窗口的显示缓冲，呈现绘制结果；不会自动绘制或清屏。
     void OpenGLRenderContext::SwapBuffer(){
        glfwSwapBuffers(m_Window);
     }
}
