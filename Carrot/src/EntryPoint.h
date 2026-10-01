#pragma once

#include "Application.h"
#include "Log.h"

#if defined(_WIN32) 

Carrot::Application* CreateApplication();

int main(int argc, char** argv){
    Carrot::Log::Init();
    CT_CORE_INFO("Log Initialized");
    Carrot::Application* app = CreateApplication();
    app->Run();
    delete app;
}

#endif
