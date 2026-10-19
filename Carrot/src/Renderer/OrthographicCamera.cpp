#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Carrot
{
    //初始化P矩阵,position和rotation,viewMatrix和VP矩阵留到ReCal里面去计算赋值
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top):
        m_ProjectionMatrix(glm::ortho(left,right,bottom,top,-1.0f,1.0f)),
        m_Position(glm::vec3(0.0f)),
        m_Rotation(0.0f)
    {
        ReCalculateProjectionViewMatrix();
    }

    void OrthographicCamera::ReCalculateProjectionViewMatrix(){
        glm::mat4 view = glm::translate(glm::mat4(1.0f),m_Position)*glm::rotate(glm::mat4(1.0f),glm::radians(m_Rotation),glm::vec3(0,0,1));

        m_ViewMatrix = glm::inverse(view);
        m_ProjectionViewMatrix = m_ProjectionMatrix*m_ViewMatrix;
    }
}