#include "Carrot.h"
class SandBox : public Carrot::Application
{
private:

public:
    SandBox() = default;
    ~SandBox() = default;
};


Carrot::Application* CreateApplication(){
    return new SandBox;
}
