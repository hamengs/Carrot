#include "WindowsWindow.h"
#include "Log.h"


#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdexcept>
#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"

namespace Carrot
{
    WindowsWindow::WindowsWindow(const WindowProps& props){
        Init(props);
    }

    WindowsWindow::~WindowsWindow(){
        ShutDown();
    }

    void WindowsWindow::Init(const WindowProps& props){
        if(!glfwInit()){
            throw std::runtime_error("Failed to initialize GLFW");
        }
        //告诉 GLFW：接下来创建窗口时，请给我一个 OpenGL 4.6 的 Core 上下文。
        //可以缺失,但是会给一个默认版本,如果写出来的话,不支持的情况下可以提前报错
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        CT_CORE_INFO("Creating window '{0}'({1} x {2})",props.Title,props.Width, props.Height);
        m_Window = glfwCreateWindow(
            static_cast<int>(props.Width),
            static_cast<int>(props.Height),
            props.Title.c_str(),
            nullptr, // 不指定全屏显示器，创建普通窗口
            nullptr  // 不与另一个窗口共享 OpenGL 资源
        );

        //设置成员变量的宽高
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        //创建失败时先清理 GLFW，再抛异常，由入口 main 捕获。
        if(!m_Window){
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        //设置opengl的上下文来自哪个窗口
        glfwMakeContextCurrent(m_Window);

        //初始化GLAD
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            glfwDestroyWindow(m_Window);
            m_Window = nullptr;
            glfwTerminate();
            throw std::runtime_error("Failed to initialize GLAD");
        }

        CT_CORE_INFO("OpenGL: {0}",reinterpret_cast<const char*>(glGetString(GL_VERSION)));

        //垂直同步,0关闭1开启
        SetVSync(false);

        //把成员数据的地址关联到 GLFW 窗口，回调通过窗口指针找回它。
        glfwSetWindowUserPointer(m_Window, &m_Data);
        //注册各个回调函数,glfw和我们自己的回调函数
        glfwSetKeyCallback(m_Window,&KeyCallbackFn);
        glfwSetCharCallback(m_Window, &CharCallbackFn);
        glfwSetWindowFocusCallback(m_Window, &WindowFocusCallbackFn);
        glfwSetCursorEnterCallback(m_Window, &CursorEnterCallbackFn);
        glfwSetMouseButtonCallback(m_Window,&MouseButtonCallbackFn);
        glfwSetScrollCallback(m_Window,&MouseScrollCallbackFn);
        glfwSetCursorPosCallback(m_Window,&CursorPosCallbackFn);
        glfwSetWindowSizeCallback(m_Window,&WindowResizeCallbackFn);
        glfwSetWindowCloseCallback(m_Window,&WindowCloseCallbackFn);
        
    }

    void WindowsWindow::MouseScrollCallbackFn(GLFWwindow* window, double XOffset, double YOffset){
        WindowsWindow::WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        if(data&&data->EventCallback){
            MouseScrolledEvent event((float)XOffset,(float)YOffset);
            data->EventCallback(event);
        }
    }

    void WindowsWindow::WindowCloseCallbackFn(GLFWwindow* window){
        WindowsWindow::WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        if(data&&data->EventCallback){
            WindowCloseEvent event;
            data->EventCallback(event);
        }
    }

    void WindowsWindow::CursorPosCallbackFn(GLFWwindow* window, double xPos, double yPos){
        WindowsWindow::WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        if(data&&data->EventCallback){
            MouseMovedEvent event((float)xPos,(float)yPos);
            data->EventCallback(event);
        }
    }

    void WindowsWindow::MouseButtonCallbackFn(GLFWwindow* window, int button, int action, int mods){
        WindowsWindow::WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        if(data&&data->EventCallback){
            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button, mods);
                    data->EventCallback(event);
                    break;
                }

                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button, mods);
                    data->EventCallback(event);
                    break;
                }

                default:
                {
                    break;
                }
            }
        }
    }

    //glfw窗口收到键盘事件后调用这个函数,action代表事件(按下,放开,按住之类的),key代表键盘代码
    void WindowsWindow::KeyCallbackFn(GLFWwindow* window, int key, int scancode, int action, int mods){
        //glfwGetWindowUserPointer通过glfw window指针得到我们之前绑定的一个自定义结构体,由于绑定只是地址,所以还得转回我们的结构体指针类型
        WindowsWindow::WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        //然后我们就可以在这里调用我们之前已经保存好的真正的回调函数
        if(data&&data->EventCallback){
            switch(action){
                case GLFW_PRESS:
                {
                    KeyPressedEvent pressedEvent(key,0,scancode,mods);
                    data->EventCallback(pressedEvent);
                    break;
                }

                case GLFW_RELEASE:
                {
                    KeyReleasedEvent releasedEvent(key,scancode,mods);
                    data->EventCallback(releasedEvent);
                    break;
                }

                case GLFW_REPEAT:
                {
                    KeyPressedEvent repeatEvent(key,1,scancode,mods);
                    data->EventCallback(repeatEvent);
                    break;
                }

                default:
                {
                    break;
                }
                
            }
        }
    }

    void WindowsWindow::CharCallbackFn(GLFWwindow* window, unsigned int codepoint){
        auto* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        if (data && data->EventCallback) {
            KeyTypedEvent event(codepoint);
            data->EventCallback(event);
        }
    }

    void WindowsWindow::WindowFocusCallbackFn(GLFWwindow* window, int focused){
        auto* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        if (data && data->EventCallback) {
            if (focused) {
                WindowFocusEvent event;
                data->EventCallback(event);
            } else {
                WindowLostFocusEvent event;
                data->EventCallback(event);
            }
        }
    }

    void WindowsWindow::CursorEnterCallbackFn(GLFWwindow* window, int entered){
        auto* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        if (data && data->EventCallback) {
            MouseEnteredEvent event(entered != 0);
            data->EventCallback(event);
        }
    }

    void WindowsWindow::WindowResizeCallbackFn(GLFWwindow* window, int width, int height){
        WindowsWindow::WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        if (!data)
            return;

        data->Width = width;
        data->Height = height;
        if(data->EventCallback){
            WindowResizeEvent event(width,height);
            data->EventCallback(event);
  
        }
    }

    void WindowsWindow::ShutDown(){
        glfwDestroyWindow(m_Window);
        m_Window = nullptr;
        //当前实现只管理一个窗口；多窗口时需统一管理 GLFW 的终止时机。
        glfwTerminate();
    }

    void WindowsWindow::PollEvents(){
        //处理已到达的窗口消息，更新状态并调用已注册的回调。
        glfwPollEvents();
    }

    void WindowsWindow::SwapBuffers(){
        //交换这个窗口的显示缓冲，呈现绘制结果；不会自动绘制或清屏。
        glfwSwapBuffers(m_Window);
        
    }

    unsigned int WindowsWindow::GetWidth() const{
        int width = 0;
        int height = 0;
        //传入两个参数地址,通过修改地址的数据得到具体窗口大小
        glfwGetWindowSize(m_Window,&width,&height);
        return static_cast<unsigned int>(width);
    }

    unsigned int WindowsWindow::GetHeight() const{
        int width = 0;
        int height = 0;
        //同上
        glfwGetWindowSize(m_Window,&width,&height);
        return static_cast<unsigned int>(height);
    }

    //设置当前运行的窗口的回调函数
    void WindowsWindow::SetEventCallback(const EventCallbackFn& callback){
        m_Data.EventCallback = callback;
    }

    bool WindowsWindow::ShouldClose() const{
        //查询关闭请求标志，不负责处理消息或销毁窗口；应用据此结束循环。
        return glfwWindowShouldClose(m_Window) == GLFW_TRUE;
    }

    void* WindowsWindow::GetNativeWindow() const{
        return m_Window;
    }

    bool WindowsWindow::IsVSync() const{
        return m_Data.isVSync;
    }

    void WindowsWindow::SetVSync(bool enable){
        m_Data.isVSync = enable;
        glfwSwapInterval(enable);
    }
} // namespace Carrot
