#pragma once

#include "Core.h"
#include <memory>
#include <spdlog/spdlog.h>

namespace Carrot
{
    class CARROT_API Log
    {
    public:
        // Call once at startup, before using the logger or starting worker threads.
        static void Init();
        static std::shared_ptr<spdlog::logger>& GetCoreLogger()
        {
            return s_CoreLogger;
        }
        static std::shared_ptr<spdlog::logger>& GetClientLogger()
        {
            return s_ClientLogger;
        }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;

    };

} // namespace Carrot

#define CT_CORE_TRACE(...)  ::Carrot::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CT_CORE_INFO(...)   ::Carrot::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CT_CORE_WARN(...)   ::Carrot::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CT_CORE_ERROR(...)  ::Carrot::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CT_CORE_FATAL(...)  ::Carrot::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define CT_CLIENT_TRACE(...)    ::Carrot::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CT_CLIENT_INFO(...)     ::Carrot::Log::GetClientLogger()->info(__VA_ARGS__)
#define CT_CLIENT_WARN(...)     ::Carrot::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CT_CLIENT_ERROR(...)    ::Carrot::Log::GetClientLogger()->error(__VA_ARGS__)
#define CT_CLIENT_FATAL(...)    ::Carrot::Log::GetClientLogger()->critical(__VA_ARGS__)
