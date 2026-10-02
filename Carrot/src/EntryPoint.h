#pragma once

#include "Application.h"
#include "Log.h"
#include <exception>
#include <memory>

#if defined(_WIN32)

Carrot::Application* CreateApplication();

int main(int argc, char** argv)
{
    Carrot::Log::Init();

    try
    {
        CT_CORE_INFO("Log Initialized");

        std::unique_ptr<Carrot::Application> app(CreateApplication());
        app->Run();
    }
    catch (const std::exception& error)
    {
        CT_CORE_ERROR("Application failed: {}", error.what());
        return 1;
    }

    return 0;
}

#endif
