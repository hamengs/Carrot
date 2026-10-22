#include "OrthographicCameraController.h"
#include "Core/Time.h"
#include "src/KeyCode.h"

namespace Carrot{

    OrthographicCameraController::OrthographicCameraController(float aspect, float zoomLevel):
        OrthographicCameraController(aspect, zoomLevel, false) {}

    OrthographicCameraController::OrthographicCameraController(
        float aspect, float zoomLevel, bool canRotate)
        : m_AspectRation(aspect),
        m_ZoomLevel(zoomLevel),
        m_CanRotate(canRotate) {
        m_Camera = std::make_shared<OrthographicCamera>(
            -aspect * zoomLevel, aspect * zoomLevel,
            -zoomLevel, zoomLevel
        );
    }

    void OrthographicCameraController::OnUpdate(){
        //线性缩放移动速度,根据窗口大小来判断
        m_CameraMoveSpeed = 5.0f*m_ZoomLevel;

        if(Carrot::Input::IsKeyDown(CT_KEY_DOWN)){
            m_CameraPos.y -= m_CameraMoveSpeed*Carrot::Time::GetDeltaTime();
        }else if(Carrot::Input::IsKeyDown(CT_KEY_UP)){
            m_CameraPos.y += m_CameraMoveSpeed*Carrot::Time::GetDeltaTime(); 
        }
        if(Carrot::Input::IsKeyDown(CT_KEY_LEFT)){
            m_CameraPos.x -= m_CameraMoveSpeed*Time::GetDeltaTime();
        }else if(Carrot::Input::IsKeyDown(CT_KEY_RIGHT)){
            m_CameraPos.x += m_CameraMoveSpeed*Carrot::Time::GetDeltaTime(); 
        }
        if(m_CanRotate){
            if(Carrot::Input::IsKeyDown(CT_KEY_Q)){
                m_Camera->SetRotation(m_Camera->GetRotation()+m_CameraRotateSpeed*Carrot::Time::GetDeltaTime());
            }else if(Carrot::Input::IsKeyDown(CT_KEY_R)){
                m_Camera->SetRotation(m_Camera->GetRotation()-m_CameraRotateSpeed*Carrot::Time::GetDeltaTime());
            }
            
        }
        
        m_Camera->SetPosition(m_CameraPos);
    }

    void OrthographicCameraController::OnEvent(Event& e){
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&OrthographicCameraController::OnMouseScrolled,this,std::placeholders::_1));
        dispatcher.Dispatch<WindowResizeEvent>(std::bind(&OrthographicCameraController::OnWindowResized,this,std::placeholders::_1));
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e){
        m_ZoomLevel -= e.GetY()*0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel,0.25f);
         m_Camera->SetProjection(
            -m_AspectRation * m_ZoomLevel,
            m_AspectRation * m_ZoomLevel,
            -m_ZoomLevel,
            m_ZoomLevel
        );
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e){
        if (e.GetWidth() == 0 || e.GetHeight() == 0){
            return false;
        }

        m_AspectRation = (float)e.GetWidth()/(float)e.GetHeight();
        m_Camera->SetProjection(
            -m_AspectRation * m_ZoomLevel,
            m_AspectRation * m_ZoomLevel,
            -m_ZoomLevel,
            m_ZoomLevel
        );
        return false;
    }
}