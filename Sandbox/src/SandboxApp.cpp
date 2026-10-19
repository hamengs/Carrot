#include "Carrot.h"
#include <imgui.h>
#include <fstream>
#include <sstream>
#include <stdexcept>


#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/OrthographicCamera.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Renderer.h"

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
        m_Shader = std::make_shared<Carrot::Shader>(vertexShader,fragShader);
    }

    void OnUpdate() override{
        //测试控制代码
        if(Carrot::Input::IsKeyDown(CT_KEY_DOWN)){
            m_CameraPos.y -= m_CameraMoveSpeed;
        }else if(Carrot::Input::IsKeyDown(CT_KEY_UP)){
            m_CameraPos.y += m_CameraMoveSpeed; 
        }
        if(Carrot::Input::IsKeyDown(CT_KEY_LEFT)){
            m_CameraPos.x -= m_CameraMoveSpeed;
        }else if(Carrot::Input::IsKeyDown(CT_KEY_RIGHT)){
            m_CameraPos.x += m_CameraMoveSpeed; 
        }
        m_Camera->SetPosition(m_CameraPos);
        //绘制代码
        Carrot::RenderCommand::SetClearColor(glm::vec4(0.1f,0.1f,0.1f,1));
        Carrot::RenderCommand::Clear();
        Carrot::Renderer::BeginScene(*m_Camera);
        Carrot::Renderer::Submit(m_Shader,m_VAO);
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
        float m_CameraMoveSpeed = 0.01f;
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

