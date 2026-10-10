#include "Carrot.h"

//测试层
class FooLayer : public Carrot::Layer{
    void OnUpdate() override{
        //CT_CLIENT_INFO("FooLayer: " + m_DebugName);
    }
    void OnEvent(Carrot::Event& e) override{
        if(e.GetEventType() == Carrot::EventType::KeyPressed){
            Carrot::KeyPressedEvent& event = (Carrot::KeyPressedEvent&)e;
            if(event.GetKeyCode()==CT_KEY_H){
                CT_CLIENT_TRACE("{0}",event.GetKeyCode());
            }
        }
    }
};

class SandBox : public Carrot::Application
{
private:

public:
    SandBox(){
        //测试代码
        //PushLayer(new FooLayer()); 
    };
    ~SandBox() = default;
};


Carrot::Application* CreateApplication(){
    return new SandBox;
}

