#define GLFW_INCLUDE_NONE

#include "ImGui/ImGuiLayer.h"
#include "Profiler/Profiler.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>

#include <stdexcept>

namespace Carrot
{
    void ImGuiLayer::Begin(){
        PROFILER_FUNCTION();
        ImGui_ImplOpenGL3_NewFrame(); // 准备渲染后端 OpenGL 后端准备
        ImGui_ImplGlfw_NewFrame(); // 更新窗口和输入相关信息
        ImGui::NewFrame();  // 正式开始构建这一帧的 UI
    }

    void ImGuiLayer::OnImGuiRender(){
        PROFILER_FUNCTION();
        //这一层自己的界面内容
        if (m_ShowDemo)
        ImGui::ShowDemoWindow(&m_ShowDemo);

    }

    //主窗口是Carrot创建的glfw窗口并且OnAttach调用的时候已经通过ImGui_ImplGlfw_InitForOpenGL(window, false);
    //指定了主窗口. 所以gui面板都被主窗口所承载然后才能绘制. 如果拖出去的话imgui会自动创建一个glfw窗口来承载拖出去的gui,
    //这就导致了会改变opengl上下文. imgui需要一个glfw窗口来承载才能绘制
    void ImGuiLayer::End(){
        PROFILER_FUNCTION();
        ImGui::Render();//整理所有窗口绘制数据
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());//把整理的数据发送给opengl执行绘制(主窗口)

        ImGuiIO& io = ImGui::GetIO();
        if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable){
            //下方update和render会改变opengl的上下文,所以先通过getcurrentcontext获取当前窗口(主窗口)的备份
            GLFWwindow* backup = glfwGetCurrentContext();

            // 创建、更新或销毁额外的系统窗口
            ImGui::UpdatePlatformWindows();
            // 绘制额外窗口的 GUI，并交换它们的缓冲区；期间会切换上下文
            ImGui::RenderPlatformWindowsDefault();

            // 恢复调用前的当前上下文，在目前的流程里就是主窗口的上下文
            glfwMakeContextCurrent(backup);
        }
    }

    void ImGuiLayer::OnAttach(){
        PROFILER_FUNCTION();
        IMGUI_CHECKVERSION(); // 版本检查
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        //启用哪些功能
        io.ConfigFlags |=
            ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |=
            ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
        io.ConfigFlags |= 
            ImGuiConfigFlags_DockingEnable;   // 面板停靠
        io.ConfigFlags |= 
            ImGuiConfigFlags_ViewportsEnable; // 拖出主窗口   
        ImGui::StyleColorsDark(); //设置样式

        //把我们的包装Window对象通过调用getNative取出底层glfwWindow,由于是void*还需要转换成需要的glfwWindow*
        auto *window = static_cast<GLFWwindow *>(m_Window->GetNativeWindow());

        // false：GLFW 回调由引擎管理，输入通过 OnEvent 转发给官方后端。
        if (!ImGui_ImplGlfw_InitForOpenGL(window, false)) {
            ImGui::DestroyContext();
            throw std::runtime_error("Failed to initialize ImGui GLFW backend");
        }

        if (!ImGui_ImplOpenGL3_Init("#version 460 core")) { //初始化imgui的opengl
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
            throw std::runtime_error(
                "Failed to initialize ImGui OpenGL backend");
        }
    }

    //依次关闭opengl glfw和imgui 不会关闭 GLFW 窗口
    void ImGuiLayer::OnDetach(){
        PROFILER_FUNCTION();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnEvent(Event& e){
        PROFILER_FUNCTION();
        auto* window = static_cast<GLFWwindow*>(m_Window->GetNativeWindow());
        EventDispatcher dispatcher(e);

        // 复用官方后端处理键码、修饰键等细节；false 表示允许其他 Layer 继续接收。
        dispatcher.Dispatch<KeyPressedEvent>([window](KeyPressedEvent& event) {
            const int action = event.GetRepeatCount() > 0 ? GLFW_REPEAT : GLFW_PRESS;
            ImGui_ImplGlfw_KeyCallback(window, event.GetKeyCode(), event.GetScanCode(),
                                      action, event.GetModifiers());
            return false;
        });
        dispatcher.Dispatch<KeyReleasedEvent>([window](KeyReleasedEvent& event) {
            ImGui_ImplGlfw_KeyCallback(window, event.GetKeyCode(), event.GetScanCode(),
                                      GLFW_RELEASE, event.GetModifiers());
            return false;
        });
        dispatcher.Dispatch<KeyTypedEvent>([window](KeyTypedEvent& event) {
            ImGui_ImplGlfw_CharCallback(window, event.GetCodepoint());
            return false;
        });
        dispatcher.Dispatch<MouseButtonPressedEvent>([window](MouseButtonPressedEvent& event) {
            ImGui_ImplGlfw_MouseButtonCallback(window, event.GetMouseButton(), GLFW_PRESS,
                                              event.GetModifiers());
            return false;
        });
        dispatcher.Dispatch<MouseButtonReleasedEvent>([window](MouseButtonReleasedEvent& event) {
            ImGui_ImplGlfw_MouseButtonCallback(window, event.GetMouseButton(), GLFW_RELEASE,
                                              event.GetModifiers());
            return false;
        });
        dispatcher.Dispatch<MouseMovedEvent>([window](MouseMovedEvent& event) {
            ImGui_ImplGlfw_CursorPosCallback(window, event.GetX(), event.GetY());
            return false;
        });
        dispatcher.Dispatch<MouseScrolledEvent>([window](MouseScrolledEvent& event) {
            ImGui_ImplGlfw_ScrollCallback(window, event.GetX(), event.GetY());
            return false;
        });
        dispatcher.Dispatch<MouseEnteredEvent>([window](MouseEnteredEvent& event) {
            ImGui_ImplGlfw_CursorEnterCallback(window, event.HasEntered() ? GLFW_TRUE : GLFW_FALSE);
            return false;
        });
        dispatcher.Dispatch<WindowFocusEvent>([window](WindowFocusEvent&) {
            ImGui_ImplGlfw_WindowFocusCallback(window, GLFW_TRUE);
            return false;
        });
        dispatcher.Dispatch<WindowLostFocusEvent>([window](WindowLostFocusEvent&) {
            ImGui_ImplGlfw_WindowFocusCallback(window, GLFW_FALSE);
            return false;
        });
    }

}
