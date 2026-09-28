#include "Application.h"
#include <cstdio>

namespace Carrot
{
    void Application::Print(){
        std::printf("Hello Carrot\n");
    }

    void Application::Run(){
        while(true);
    }

    Application::Application(/* args */)
    {

    }
    
    Application::~Application()
    {
        
    }
} // namespace Carrot
