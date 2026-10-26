
#define GLFW_INCLUDE_NONE
#include "Core/Time.h"

#include <GLFW/glfw3.h>

//不同平台的话就编译或者配置文件不同就行
namespace Carrot
{

    float Time::GetPlatformTime(){
        return static_cast<float>(glfwGetTime());
    }

}