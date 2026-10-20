#include "Core/Time.h"

namespace Carrot
{
    //先初始化绝对时间,deltaTime需要在初始化后才能进行赋值,Init后第一次调用OnUpdate时
    void Time::Init(){
        s_Time = GetPlatformTime();
        s_DeltaTime = 0.0f;
    }

    void Time::OnUpdate(){
        float now = GetPlatformTime();
        s_DeltaTime = now-s_Time;
        s_Time = now;
    }

}