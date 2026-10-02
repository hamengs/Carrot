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
        bool IsVSync() const;
        void SetVSync(bool enabled);

    private:
        GLFWwindow* m_Window = nullptr;
        void ShutDown();
        void Init(const WindowProps& props);

        struct WindowData{
            bool isVSync =false;
            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };
}
