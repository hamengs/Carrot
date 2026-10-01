#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Carrot
{
    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

    //初始化Logger
    void Log::Init()
    {

        if (s_CoreLogger)
            return;


        s_CoreLogger = spdlog::stdout_color_mt("CARROT");   //创建Logger
        s_CoreLogger->set_pattern("%^[%T] [%n] [%l] %v%$"); //设置输出格式,时间,日志器名称,等级(info,error...),传入的内容
        s_CoreLogger->set_level(spdlog::level::trace);      //设置最低输出等级 trace代表trace上的info,error warn等全部输出

        if (s_ClientLogger)
            return;

        s_ClientLogger = spdlog::stdout_color_mt("SANDBOX");
        s_ClientLogger->set_pattern("%^[%T] [%n] [%l] %v%$");
        s_ClientLogger->set_level(spdlog::level::trace);
    }
}
