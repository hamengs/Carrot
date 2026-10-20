#pragma once

namespace Carrot
{
    class Time{
    public:

        static float GetTime(){return s_Time;}
        static float GetTimeMilliSeconds(){return s_Time*1000;}
        static float GetDeltaTime(){return s_DeltaTime;}

    private:
        friend class Application;
        
        static void Init();//初始化
        
        static void OnUpdate();//每帧由application调用来保持更新

        static float GetPlatformTime();

        inline static float s_Time = 0.0f;
        inline static float s_DeltaTime = 0.0f;
    };
    
}