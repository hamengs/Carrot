#include "ImGuiLayer.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace Carrot
{
    void ImGuiLayer::OnAttach(){
        IMGUI_CHECKVERSION(); // 版本检查
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |=
            ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |=
            ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

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
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnEvent(Event& e){
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

    void ImGuiLayer::OnUpdate(){

        ImGui_ImplOpenGL3_NewFrame(); // 准备渲染后端 OpenGL 后端准备
        ImGui_ImplGlfw_NewFrame(); // 更新窗口和输入相关信息
        ImGui::NewFrame();  // 正式开始构建这一帧的 UI

        if (m_ShowDemo)
        ImGui::ShowDemoWindow(&m_ShowDemo);

        ImGui::Render();//整理绘制数据
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());//把整理的数据发送给opengl执行绘制
    }
}
