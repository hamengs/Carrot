#pragma once

#include "Application.h"
#include <iostream>

#if defined(_WIN32) 

Carrot::Application* CreateApplication();

int main(int argc, char** argv){
    std::cout<<"Carrot Engine Start"<<std::endl;
    Carrot::Application* app = CreateApplication();
    app->Run();
    delete app;
}

#endif
