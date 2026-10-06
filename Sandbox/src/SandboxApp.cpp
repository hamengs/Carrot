#include "Carrot.h"

class FooLayer : public Carrot::Layer{
    void OnUpdate() override{
        //CT_CLIENT_INFO("FooLayer: " + m_DebugName);
    }
};

class SandBox : public Carrot::Application
{
private:

public:
    SandBox(){
        PushLayer(new FooLayer());
    };
    ~SandBox() = default;
};


Carrot::Application* CreateApplication(){
    return new SandBox;
}

