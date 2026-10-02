#include "Application.h"
#include <cstdio>
#include "Window.h"
#include "Log.h"

namespace Carrot
{
    void PrintEvent(Event& event){
        CT_CORE_INFO("Received event: {}", event.ToString());
    }

    void Application::Run(){


        //创建失败时异常传到入口 main，由入口记录错误并退出。
        std::unique_ptr<Window> window = Window::Create();
        window->SetEventCallback(PrintEvent); //保存处理函数，此处并不调用 PrintEvent

        while(!window->ShouldClose()){
            window->OnUpdate();
        }
    }

    Application::Application(/* args */)
    {

    }

    Application::~Application()
    {

    }
} // namespace Carrot
