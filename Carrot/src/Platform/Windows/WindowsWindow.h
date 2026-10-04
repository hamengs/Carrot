#pragma once

#include "Window.h"

struct GLFWwindow;

namespace Carrot{

    class WindowsWindow : public Window{
    public:
        explicit WindowsWindow(const WindowProps& props);
        ~WindowsWindow() override;

        void OnUpdate() override;

        unsigned int GetWidth() const override;
        unsigned int GetHeight() const override;

        
        bool ShouldClose() const override;
        void SetEventCallback(const EventCallbackFn& callback) override;
        static void KeyCallbackFn(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void WindowResizeCallbackFn(GLFWwindow* window,int width, int height);
        static void WindowCloseCallbackFn(GLFWwindow* window);
        static void CursorPosCallbackFn(GLFWwindow* window, double xPos, double yPos);
        static void MouseButtonCallbackFn(GLFWwindow* window, int button, int action, int mods);
        static void MouseScrollCallbackFn(GLFWwindow* window, double XOffset, double YOffset);

        bool IsVSync() const; //
        void SetVSync(bool enabled);

    private:
        GLFWwindow* m_Window = nullptr;
        void ShutDown(); //关闭窗口函数,在析构时调用
        void Init(const WindowProps& props); //初始化函数,在构造时调用,需要一个props来指定初始化参数

        //当前窗口的一些数据,长宽也可以加入,暂时没加入,只有垂直同步和当前窗口的回调函数,
        //不放在windows.h是因为这些是运行时数据,window调用具体实现类方法来创建窗口所以不需要运行时的数据,最终取决于实现方式
        struct WindowData{
            bool isVSync =false;
            EventCallbackFn EventCallback;
            int Width;
            int Height;
        };
        
        WindowData m_Data;
    };
}
