#pragma once

#include "Core/Input.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"
#include "Renderer/OrthographicCamera.h"

namespace Carrot
{
    //相机控制类,访问相机,更新相机都通过这个类来操作
    class OrthographicCameraController{
    public:
        OrthographicCameraController(float aspectRatio, float zoomLevel);
        OrthographicCameraController(float aspectRatio, float zoomLevel,bool canRotate);

        void OnUpdate();
        void OnEvent(Event& e);
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);

        inline OrthographicCamera& GetCamera(){return *m_Camera;}
        inline const OrthographicCamera& GetCamera() const {return *m_Camera;}
      
    private:
        float m_AspectRation;
        float m_ZoomLevel;
        Ref<OrthographicCamera> m_Camera;
        glm::vec3 m_CameraPos = glm::vec3(0.0f);
        float m_CameraMoveSpeed = 5.0f;
        float m_CameraRotateSpeed = 5.0f;
        bool m_CanRotate = false;
    };
}
