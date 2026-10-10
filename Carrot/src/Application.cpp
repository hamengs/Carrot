#include "Application.h"
#include <cstdio>
#include "Window.h"
#include "Log.h"
#include <GLFW/glfw3.h>
#include "ImGui/ImGuiLayer.h"
#include "Input.h"

namespace Carrot
{


    void Application::Run(){

        while(m_Running){
            Input::BeginFrame();
            // 先处理事件填入本帧输入，再让各层查询。
            m_Window->PollEvents();
            if (!m_Running)
                break;
            glClearColor(0,1,0,1);
            glClear(GL_COLOR_BUFFER_BIT);
            for(auto layer : m_Layers){
                layer->OnUpdate();
            }
            m_Window->SwapBuffers();
        }
    }

    Application::Application(/* args */)
    {
        //创建失败时异常传到入口 main，由入口记录错误并退出。
        m_Window = Window::Create();
        //std::bind生成一个可调用对象,一般用auto保存,具体标准由实现库决定,
        //OnEvent 是成员函数，绑定 this 指定当前应用对象；_1 将回调收到的第一个参数传给 OnEvent。
        m_Window->SetEventCallback(std::bind(&Application::OnEvent,this,std::placeholders::_1)); //保存处理函数，此处并不实际调用
        PushOverLayer(new ImGuiLayer(m_Window.get())); //get相当于获取智能指针

        //初始化Input系统,因为window在application创建所以在这里初始化需要window的系统
        Input::Init(*m_Window);
    }

    Application::~Application()
    {
        //关闭释放输入系统,谁初始化谁负责释放
        Input::ShutDown();
    }

    void Application::OnEvent(Event& event){
        // 原始输入先记录，不能因为某个 Layer 消费事件而漏掉松开。
        Input::OnEvent(event);
        CT_CORE_INFO("Received event: {}", event.ToString());
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<WindowCloseEvent>
        (std::bind(&Application::OnWindowClose,this, std::placeholders::_1));

        for(auto it = m_Layers.end(); it!=m_Layers.begin();){
            //先检查是否解决再去--,和调用OnEvent,否则已完成的事件依然会调用一次OnEvent
            if(event.Handled()){
                break;
            }
            --it;
            (*it)->OnEvent(event);
        }

    }

    bool Application::OnWindowClose(WindowCloseEvent& e){
        m_Running = false;
        return true;
    }

    void Application::PushLayer(Layer* layer){
        m_Layers.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverLayer(Layer* layer){
        //加入时记得调用OnAttach初始化
        m_Layers.PushOverLayer(layer);
        layer->OnAttach();
    }
} // namespace Carrot
