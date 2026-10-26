#pragma once

#include "Core/Application.h"
#include "Core/Log.h"
#include "Profiler/Profiler.h"

#include <exception>
#include <memory>

#if defined(_WIN32)

Carrot::Application* CreateApplication();

int main()
{
    Carrot::Log::Init();

    try
    {
        CT_CORE_INFO("Log Initialized");

        Carrot::Scope<Carrot::Application> app;
        {
            PROFILER_SESSION("Startup", "ProfilerResult/startup.json");
            app.reset(CreateApplication());
        }
        {
            PROFILER_SESSION("Runtime", "ProfilerResult/runtime.json");
            app->Run();
        }
        {
            PROFILER_SESSION("Shutdown", "ProfilerResult/shutdown.json");
            app.reset();
        }
    }
    catch (const std::exception& error)
    {
        CT_CORE_ERROR("Application failed: {}", error.what());
        return 1;
    }

    return 0;
}

#endif
