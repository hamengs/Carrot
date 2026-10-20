#include "Carrot.h"
#include <imgui.h>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/OrthographicCamera.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Renderer.h"
#include "Renderer/Material.h"

//测试层
class FooLayer : public Carrot::Layer{
public:

    //测试读取文件代码,后期删除
    static std::string ReadFile(const std::string& path)
    {
        std::ifstream file(path);

        if (!file.is_open())
            throw std::runtime_error("Cannot open shader file: " + path);

        std::ostringstream contents;
        contents << file.rdbuf();

        return contents.str();
    }

    FooLayer():Layer("FooLayer"){
        //三角形测试代码
        float aspect = 1920.0f / 1080.0f;
        m_Camera = std::make_shared<Carrot::OrthographicCamera>(-aspect, aspect,-1.0f,1.0f);

        float vertices[3][3] = {
            {-0.5,-0.5,0.0},
            {0.5,-0.5,0.0},
            {0.0,0.5,0.0}
        };

        unsigned int indices[3] = {0,1,2};
        //让工厂决定创建的对象,Create已经new了对象了,这里不能用make unique,使用reset把new出来的对象转移给智能指针管理
        m_VAO.reset(Carrot::VertexArray::Create());
        m_VAO->Bind();

        std::shared_ptr<Carrot::VertexBuffer> vbo(Carrot::VertexBuffer::Create(vertices[0], sizeof(vertices)));
        vbo->SetLayout({
            {Carrot::ShaderDataType::FLOAT3, "a_Postion"},
        });

        m_VAO->AddVertexBuffer(vbo);

        std::shared_ptr<Carrot::IndexBuffer> ib(Carrot::IndexBuffer::Create(indices,sizeof(indices)));

        m_VAO->SetIndexBuffer(ib);

        const std::string vertexShader = ReadFile("Carrot/src/Shaders/vertexShader.vs");
        const std::string fragShader = ReadFile("Carrot/src/Shaders/fragShader.fs");
        m_Shader = Carrot::Shader::Create(vertexShader,fragShader);

        //创建材质
        redMaterial = new Carrot::Material(m_Shader);
        blueMaterial = new Carrot::Material(m_Shader);

        redMaterial->SetColor(glm::vec4(1.0f,0.0f,0.0f,1.0f));
        blueMaterial->SetColor(glm::vec4(0.0f,0.0f,1.0f,1.0f));
    }

    void OnUpdate() override{
        //测试控制代码
        if(Carrot::Input::IsKeyDown(CT_KEY_DOWN)){
            m_CameraPos.y -= m_CameraMoveSpeed*Carrot::Time::GetDeltaTime();
        }else if(Carrot::Input::IsKeyDown(CT_KEY_UP)){
            m_CameraPos.y += m_CameraMoveSpeed*Carrot::Time::GetDeltaTime(); 
        }
        if(Carrot::Input::IsKeyDown(CT_KEY_LEFT)){
            m_CameraPos.x -= m_CameraMoveSpeed*Carrot::Time::GetDeltaTime();
        }else if(Carrot::Input::IsKeyDown(CT_KEY_RIGHT)){
            m_CameraPos.x += m_CameraMoveSpeed*Carrot::Time::GetDeltaTime(); 
        }
        m_Camera->SetPosition(m_CameraPos);
        //三角形模型控制
        if(Carrot::Input::IsKeyDown(CT_KEY_S)){
            m_TrianglePos.y -= m_TriangleMoveSpeed*Carrot::Time::GetDeltaTime();
        }else if(Carrot::Input::IsKeyDown(CT_KEY_W)){
            m_TrianglePos.y += m_TriangleMoveSpeed*Carrot::Time::GetDeltaTime(); 
        }
        if(Carrot::Input::IsKeyDown(CT_KEY_A)){
            m_TrianglePos.x -= m_TriangleMoveSpeed*Carrot::Time::GetDeltaTime();
        }else if(Carrot::Input::IsKeyDown(CT_KEY_D)){
            m_TrianglePos.x += m_TriangleMoveSpeed*Carrot::Time::GetDeltaTime(); 
        }

        
        //绘制代码
        Carrot::RenderCommand::SetClearColor(glm::vec4(0.1f,0.1f,0.1f,1));
        Carrot::RenderCommand::Clear();
        Carrot::Renderer::BeginScene(*m_Camera);
        for(int i = 0; i<5; i++){
            for(int j = 0; j<5; j++){
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::scale(model,glm::vec3(0.1f,0.1f,1.0f));
                model = glm::translate(model,glm::vec3(1.0f*j,1.0f*i,0.0f));
                model = glm::translate(model,m_TrianglePos);
                if(j%2==0){
                    Carrot::Renderer::Submit(redMaterial,m_VAO,model);
                }else{
                    Carrot::Renderer::Submit(blueMaterial,m_VAO,model);
                }

            }
        }

        Carrot::Renderer::EndScene();

    }
    void OnEvent(Carrot::Event& e) override{
        if(e.GetEventType() == Carrot::EventType::KeyPressed){
            Carrot::KeyPressedEvent& event = (Carrot::KeyPressedEvent&)e;
            if(event.GetKeyCode()==CT_KEY_H){
                CT_CLIENT_TRACE("{0}",event.GetKeyCode());
            }
        }
    }
    void OnImGuiRender() override{
        ImGui::Begin("Title");
        ImGui::Text("Hello World");
        ImGui::End();
    }

private:
        std::shared_ptr<Carrot::VertexArray> m_VAO;
        std::shared_ptr<Carrot::Shader> m_Shader;
        std::shared_ptr<Carrot::OrthographicCamera> m_Camera;
        glm::vec3 m_CameraPos = glm::vec3(0.0f);
        float m_CameraMoveSpeed = 5.0f;

        glm::vec3 m_TrianglePos = glm::vec3(0.0f);
        float m_TriangleMoveSpeed = 5.0f;

        //材质
        Carrot::Material* redMaterial;
        Carrot::Material* blueMaterial;

};

class SandBox : public Carrot::Application
{
private:

public:
    SandBox(){
        //测试代码
        PushLayer(new FooLayer()); 
    };
    ~SandBox() = default;
};


Carrot::Application* CreateApplication(){
    return new SandBox;
}

