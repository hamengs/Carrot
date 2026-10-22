#include "Carrot.h"
#include <imgui.h>
#include <stdexcept>
#include <glm/gtc/matrix_transform.hpp>

//测试层
class FooLayer : public Carrot::Layer{
public:

    FooLayer():Layer("FooLayer"){
        //三角形测试代码
        float aspect = 1920.0f / 1080.0f;
        m_CameraController = std::make_shared<Carrot::OrthographicCameraController>(aspect,1.0f);

        float vertices[3][3] = {
            {-0.5,-0.5,0.0},
            {0.5,-0.5,0.0},
            {0.0,0.5,0.0}
        };

        float squd[4][5] = {
            // 位置 x, y, z         UV u, v
            {-0.5f, -0.5f, 0.0f,   0.0f, 0.0f}, // 左下
            { 0.5f, -0.5f, 0.0f,   1.0f, 0.0f}, // 右下
            { 0.5f,  0.5f, 0.0f,   1.0f, 1.0f}, // 右上
            {-0.5f,  0.5f, 0.0f,   0.0f, 1.0f}, // 左上
        };

        unsigned int indicesSqud[] = {
            0, 1, 2,
            2, 3, 0
        };

        unsigned int indices[3] = {0,1,2};
        //让工厂决定创建的对象,Create已经new了对象了,这里不能用make unique,使用reset把new出来的对象转移给智能指针管理
        m_VAO.reset(Carrot::VertexArray::Create());
        m_VAO->Bind();

        Carrot::Ref<Carrot::VertexBuffer> vbo(Carrot::VertexBuffer::Create(squd[0], sizeof(squd)));
        vbo->SetLayout({
            {Carrot::ShaderDataType::FLOAT3, "a_Postion"},
            {Carrot::ShaderDataType::FLOAT2, "a_TexCoord"}
        });

        m_VAO->AddVertexBuffer(vbo);

        Carrot::Ref<Carrot::IndexBuffer> ib(Carrot::IndexBuffer::Create(indicesSqud,sizeof(indicesSqud)));

        m_VAO->SetIndexBuffer(ib);

        m_Shaders.Load("faceShader","Sandbox/assets/Shaders/vertexShader.vs","Sandbox/assets/Shaders/fragShader.fs");

        m_Texture2D = Carrot::Texture2D::Create("Sandbox/assets/Pictures/awesomeFace.png");

        //创建材质
        fooMaterial = new Carrot::Material(m_Shaders.Get("faceShader"));
        fooMaterial->SetTexture2D(m_Texture2D);

        
    }

    void OnUpdate() override{
        //tick相机控制器
        m_CameraController->OnUpdate();

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
        Carrot::Renderer::BeginScene(m_CameraController->GetCamera());
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model,glm::vec3(1.0f,1.0f,1.0f));
        model = glm::translate(model,m_TrianglePos);
        Carrot::Renderer::Submit(*fooMaterial,m_VAO,model);

        Carrot::Renderer::EndScene();

    }
    
    void OnEvent(Carrot::Event& e) override{
        m_CameraController->OnEvent(e);
    }

    void OnImGuiRender() override{
        ImGui::Begin("Material Editor");

        ImGui::End();
    }

private:
        Carrot::ShaderLibrary m_Shaders;
        Carrot::Ref<Carrot::VertexArray> m_VAO;
        Carrot::Ref<Carrot::Shader> m_Shader;
        Carrot::Ref<Carrot::Texture2D> m_Texture2D;
        Carrot::Ref<Carrot::OrthographicCameraController> m_CameraController;


        glm::vec3 m_TrianglePos = glm::vec3(0.0f);
        float m_TriangleMoveSpeed = 5.0f;

        //材质
        Carrot::Material* fooMaterial;
        

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

