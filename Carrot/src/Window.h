#pragma once

#include "Core.h"
#include <memory>
#include <string>
#include "Events/Event.h"
#include <functional>

namespace Carrot
{
    //创建窗口时需要的结构体数据,可以自定义窗口名称,长,宽
    struct WindowProps{
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(std::string title = "Carrot Engine", unsigned int width = 1920, unsigned int height = 1080)
            :Title(title), Width(width), Height(height){

            }
    };

    class CARROT_API Window{
    public:

        using EventCallbackFn = std::function<void(Event&)>; //回调类型：接收事件引用，返回 void
        virtual ~Window() = default; //通过 Window 指针销毁时执行派生类析构，具体资源由派生类释放

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;


        virtual bool ShouldClose() const = 0; //窗口是否应该关闭,是application主循环的结束条件
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0; //设置回调函数,需要一个回调函数,这个函数返回void接受一个event

        //unique_ptr 在正常离开作用域或异常展开栈时释放对象（不保证进程强制终止时清理）。
        //static 允许直接用 Window::Create 调用，props 指定标题、宽度和高度。
        static std::unique_ptr<Window> Create(
            const WindowProps& props = WindowProps()
        );

    };

} // namespace Carrot
