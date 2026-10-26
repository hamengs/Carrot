#include "Carrot.h"


#include <imgui.h>
#include <stdexcept>
#include "Core/EntryPoint.h"
#include "Sandbox2D.h"

class SandBox : public Carrot::Application
{
private:

public:
    SandBox(){
        //测试代码
        PushLayer(new Sandbox2D()); 
    };
    ~SandBox() = default;
};


Carrot::Application* CreateApplication(){
    return new SandBox;
}

