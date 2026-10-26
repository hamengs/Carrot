#pragma once

#include "Core/Core.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


namespace Carrot{

    struct ProfilerResult{
        std::string Name;
        double Duration;
        double Start;
        double End;
    };

    class Profiler{
    public:
        static Profiler& Get(){
            static Profiler instance;
            return instance;
        }
        const std::vector<ProfilerResult>& GetResults() const {return m_Results;}
        void StartSession(const std::string& path);
        void WriteProfiler(ProfilerResult& result);
        void EndSession();
        void ClearResults(){
            m_Results.clear();
        }
    private:
        std::ofstream m_OutputStream;
        bool m_SessionActive =false;
        bool m_FirstEvent = true;
        std::vector<ProfilerResult> m_Results;
    
    };
    
    class ProfileSession{
    public:
        explicit ProfileSession(const std::string& path){
            ::Carrot::Profiler::Get().StartSession(path);
        }
        ~ProfileSession(){
            ::Carrot::Profiler::Get().EndSession();
        }
        
        ProfileSession(const ProfileSession&) = delete;
        ProfileSession& operator=(const ProfileSession&) = delete;
    };

    //计时器类,用生命周期来计时
    template<typename FN>
    class Timer {
    public:
        //构造时记录start
        Timer(const std::string& name, FN&& func):m_Start(std::chrono::steady_clock::now()),m_Stopped(false),m_Name(name),m_Func(func){
            
        }
        //析构时记录停止
        ~Timer(){
            if(!m_Stopped){
                Stop();
            }
        }
        //析构时调用,记录停止并把数据传递给结构体方便传递给外界
        void Stop(){
            if(m_Stopped){
                return;
            }
            m_Stopped = true;
            m_End = std::chrono::steady_clock::now();
            m_ProfilerResult.Duration = std::chrono::duration<double,std::milli>(m_End-m_Start).count();
            m_ProfilerResult.Start = std::chrono::duration<double,std::milli>(m_Start.time_since_epoch()).count();
            m_ProfilerResult.End = std::chrono::duration<double,std::milli>(m_End.time_since_epoch()).count();
            m_ProfilerResult.Name = m_Name;

            m_Func(m_ProfilerResult);
        }
    private:
        std::string m_Name;
        ProfilerResult m_ProfilerResult;
        bool m_Stopped;
        std::chrono::steady_clock::time_point m_Start;
        std::chrono::steady_clock::time_point m_End;
        FN m_Func;
    };

    //计时器宏方便不用每次创建都写lambda,但是好像还要两层封装,懒得理解了先不管有需要再弄
    #define CARROT_PROFILE_ENABLED 0 // 总开关：0 关闭所有计时
    #define CARROT_PROFILE_JSON 1    // 文件开关：0 仅保留内存收集

    #if CARROT_PROFILE_ENABLED

    #define PROFILER_SCOPE(name) \
        ::Carrot::Timer CT_CONCAT(timer, __LINE__)( \
            (name), [](::Carrot::ProfilerResult& result) { \
                ::Carrot::Profiler::Get().WriteProfiler(result); \
            })

    #define PROFILER_SESSION(name, path) \
        ::Carrot::ProfileSession CT_CONCAT(profileSession, __LINE__)(path); \
        PROFILER_SCOPE(name)

    #define PROFILER_FUNCTION() PROFILER_SCOPE(__func__)

    #else

    #define PROFILER_SCOPE(name)
    #define PROFILER_SESSION(name, path)
    #define PROFILER_FUNCTION()

    #endif

}
