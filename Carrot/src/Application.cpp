#include "Application.h"
#include <cstdio>
#include "Window.h"
#include "Log.h"
#include <GLFW/glfw3.h>


namespace Carrot
{


    void Application::Run(){

        while(m_Running){
            glClearColor(0,1,0,1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
    }

    Application::Application(/* args */)
    {
        //创建失败时异常传到入口 main，由入口记录错误并退出。
        m_Window = Window::Create();
        //std::bind生成一个可调用对象,一般用auto保存,具体标准由实现库决定,
        //OnEvent 是成员函数，绑定 this 指定当前应用对象；_1 将回调收到的第一个参数传给 OnEvent。
        m_Window->SetEventCallback(std::bind(&Application::OnEvent,this,std::placeholders::_1)); //保存处理函数，此处并不实际调用
    }

    Application::~Application()
    {

    }

    void Application::OnEvent(Event& event){
        CT_CORE_INFO("Received event: {}", event.ToString());
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose,this, std::placeholders::_1));
    }

    bool Application::OnWindowClose(WindowCloseEvent& e){
        m_Running = false;
        return true;
    }
} // namespace Carrot
