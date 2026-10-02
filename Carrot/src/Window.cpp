#include "Window.h"
#include "Platform/Windows/WindowsWindow.h"

namespace Carrot
{
    //create的具体实现,使用make_unique来创建一个派生类WindowsWindow,如果是别的平台,到时候会在下面实现不一样的类型
    std::unique_ptr<Window> Window::Create(const WindowProps& props){
        return std::make_unique<WindowsWindow>(props);
    }
} // namespace Carrot
