#include "Sandbox2D.h"
#include "Renderer/Renderer2D.h"
#include <imgui.h>




    Sandbox2D::Sandbox2D():Layer("Sandbox2D"){
        PROFILER_FUNCTION();
        m_CameraController = std::make_shared<Carrot::OrthographicCameraController>(1920.0f / 1080.0f, 1.0f);
    }
 

    void Sandbox2D::OnAttach(){
        PROFILER_FUNCTION();
        m_Texture2D = Carrot::Texture2D::Create("Sandbox/assets/Pictures/cryFace.png");
        test_Texture2D = Carrot::Texture2D::Create("Sandbox/assets/Pictures/awesomeFace.png");

    }

    void Sandbox2D::OnDetach(){
        PROFILER_FUNCTION();
    }

    void Sandbox2D::OnUpdate(){
        PROFILER_FUNCTION();
        //tick相机控制器
        m_CameraController->OnUpdate(); 

        //绘制代码
        Carrot::RenderCommand::SetClearColor(glm::vec4(0.1f,0.1f,0.1f,1));
        Carrot::RenderCommand::Clear();
        Carrot::Renderer2D::BeginScene(m_CameraController->GetCamera());
        Carrot::Renderer2D::DrawQuad(glm::vec3{0.0f,0.0f,0.0f},glm::vec2{1.0f,1.0f},glm::vec4{0.0f,0.0f,1.0f,1.0f});
        Carrot::Renderer2D::DrawQuad(glm::vec3{1.0f,0.0f,0.1f},glm::vec2{1.0f,1.0f},glm::vec4{0.0f,1.0f,0.0f,1.0f});
        Carrot::Renderer2D::DrawQuad(glm::vec3{0.0f,1.0f,0.1f},glm::vec2{1.0f,1.0f},m_Texture2D, glm::vec4(0.5f));
        Carrot::Renderer2D::DrawQuad(glm::vec3{0.0f,-1.0f,0.1f},glm::vec2{2.0f,2.0f},45.0f,test_Texture2D, glm::vec4(1.0f));
        Carrot::Renderer2D::EndScene();
    }

    void Sandbox2D::OnEvent(Carrot::Event& e){
        PROFILER_FUNCTION();
        m_CameraController->OnEvent(e);
    }

    void Sandbox2D::OnImGuiRender(){
        PROFILER_FUNCTION();
        Carrot::Profiler& profiler = ::Carrot::Profiler::Get();
        ImGui::Begin("Profiler");
        for(Carrot::ProfilerResult result: profiler.GetResults()){
            ImGui::Text("%s %.3fms,",result.Name.c_str(),result.Duration);
        }
        ImGui::End();
        profiler.ClearResults();
    }
