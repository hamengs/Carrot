#pragma once

#include <glm/glm.hpp>

namespace Carrot
{
    class OrthographicCamera{
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        const glm::mat4& GetProjectionViewMatrix() const {return m_ProjectionViewMatrix;}
        const glm::mat4& GetProjectionMatrix() const {return m_ProjectionMatrix;}
        const glm::mat4& GetViewMatrix() const {return m_ViewMatrix;}

        const float GetRotation() const {return m_Rotation;}
        const glm::vec3& GetPosition() const{return m_Position;}

        //修改成员变量后重新计算以获得生效
        void SetPosition(glm::vec3 position){m_Position = position; ReCalculateProjectionViewMatrix();}
        void SetRotation(float rotation){m_Rotation = rotation; ReCalculateProjectionViewMatrix();}
        void SetProjection(float left, float right, float bottom, float top);
        void ReCalculateProjectionViewMatrix();

    private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionViewMatrix;
        glm::vec3 m_Position;
        float m_Rotation;
    };
}
