#include "Renderer/Renderer2D.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Texture.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/RenderCommand.h"
#include "Profiler/Profiler.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Carrot{

    struct QuadVertex {
        glm::vec3 Position;
        glm::vec4 Color;
    };

    struct Renderer2DStorage{
        static constexpr uint32_t MaxQuads = 10000;
        static constexpr uint32_t MaxVertices = 4*MaxQuads;
        static constexpr uint32_t MaxIndices = MaxQuads * 6;
        uint32_t MaxData[MaxVertices][7];

        Ref<VertexArray> QuadVertexArray;
        // 提交批次时需要调用 SetData，所以直接保存 VBO
        Ref<VertexBuffer> QuadVertexBuffer;
        //Ref<Material> QuadMaterial;
        Ref<ShaderLibrary> QuadShaders;
        // CPU 顶点数组的起点
        QuadVertex* QuadVertexBufferBase = nullptr;
        // CPU 顶点数组下一次写入的位置
        QuadVertex* QuadVertexBufferPtr = nullptr;

        uint32_t QuadIndexCount = 0;

        Ref<Texture2D> WhiteTexture;
        glm::mat4 ProjectionViewMatrix;
    };

    static Renderer2DStorage* s_Render2D_Data;

    void Renderer2D::Init(){
        PROFILER_FUNCTION();

        s_Render2D_Data = new Renderer2DStorage();
        Renderer2DStorage data = *s_Render2D_Data;


        //让工厂决定创建的对象
        s_Render2D_Data->QuadVertexArray = Carrot::VertexArray::Create();
        s_Render2D_Data->QuadVertexArray->Bind();

        data.QuadVertexBuffer = std::make_shared<Carrot::VertexBuffer>(Carrot::VertexBuffer::Create(sizeof(s_Render2D_Data->MaxData)));

        data.QuadVertexBuffer->SetLayout({
            {Carrot::ShaderDataType::FLOAT3, "a_Postion"},
            {Carrot::ShaderDataType::FLOAT4, "a_Color"},
        });

        
        s_Render2D_Data->QuadVertexArray->AddVertexBuffer(data.QuadVertexBuffer);

        data.QuadVertexBufferBase = new QuadVertex[Renderer2DStorage::MaxVertices];
        data.QuadVertexBufferPtr = data.QuadVertexBufferBase;

        auto* indices = new uint32_t[Renderer2DStorage::MaxIndices];

        uint32_t offset = 0;

        for(int i = 0; i<Renderer2DStorage::MaxIndices; i+=6){
            indices[0+i] = offset+0;
            indices[1+i] = offset+1;
            indices[2+i] = offset+2;

            indices[3+i] = offset+2;
            indices[4+i] = offset+3;
            indices[5+i] = offset+0;

            offset+=4;
        }

        Ref<IndexBuffer> ib = std::make_shared<IndexBuffer>(IndexBuffer::Create(indices,sizeof(indices)));

        s_Render2D_Data->QuadVertexArray->SetIndexBuffer(ib);
        // OpenGL 创建索引缓冲区时已复制数据
        delete[] indices;

        s_Render2D_Data->QuadShaders = std::make_shared<ShaderLibrary>();
        s_Render2D_Data->QuadShaders->Load("quadShader","Sandbox/assets/Shaders/QuadShader/quadVertex.glsl","Sandbox/assets/Shaders/QuadShader/quadFrag.glsl");
        Ref<Shader> shader = s_Render2D_Data->QuadShaders->Get("quadShader");
        s_Render2D_Data->WhiteTexture = Texture2D::Create(1,1);
        uint32_t whiteData = 0xffffffff;
        s_Render2D_Data->WhiteTexture->SetData(&whiteData,sizeof(uint32_t));

    }

    void Renderer2D::ShunDown(){
        PROFILER_FUNCTION();
        delete s_Render2D_Data;
    }

    void Renderer2D::StartBatch(){
        auto& data = *s_Render2D_Data;

        data.QuadVertexBufferPtr = data.QuadVertexBufferBase;
        data.QuadIndexCount = 0;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera){
        PROFILER_FUNCTION();
        auto& data = *s_Render2D_Data;
        Ref<Shader> shader = s_Render2D_Data->QuadShaders->Get("quadShader");
        shader->Bind();
        shader->SetMat4("ProjectionViewMatrix",camera.GetProjectionViewMatrix());
        s_Render2D_Data->ProjectionViewMatrix = camera.GetProjectionViewMatrix();
        StartBatch();
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color){
        DrawQuad(glm::vec3(position,0.0f),size,0.0f,s_Render2D_Data->WhiteTexture,color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color){
        auto& data = *s_Render2D_Data;
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model,position);
        model = glm::scale(model,glm::vec3(size,1.0f));


        data.QuadVertexBufferPtr++;
    }
 
    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const float& angle, const glm::vec4& color){
        DrawQuad(glm::vec3(position,0.0f),size,angle,s_Render2D_Data->WhiteTexture,color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const float& angle, const glm::vec4& color){
        DrawQuad(position,size,angle,s_Render2D_Data->WhiteTexture,color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4 tintColor){
        DrawQuad(position,size,0.0f,texture,tintColor);
    }

    //这个函数要画自己的纹理的话就要把原来的白色纹理绑定成自己的纹理
    //tintColor如果要不想tint就传递1.0,如果是被上面两个重载函数调用的话,也就是想画纯color,那么就会被设置为他们的color
    //同时因为上面的函数调用的方法绑定的白色纹理,所以最后画出来的颜色是他们自己设定的颜色,1.0f白色*任何颜色都为那个颜色本身;
    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const float& angle, const Ref<Texture2D>& texture, const glm::vec4 tintColor){
        PROFILER_FUNCTION();
        Ref<Shader> shader = s_Render2D_Data->QuadShaders->Get("quadShader");
        
        if(texture){
            texture->Bind(1);
        }else{
            s_Render2D_Data->WhiteTexture->Bind(1);
        }
        shader->Bind();
        shader->SetFloat4("u_Color",tintColor);
        shader->SetInt("u_Texture", 1);
        shader->SetMat4("ProjectionViewMatrix",s_Render2D_Data->ProjectionViewMatrix);
        glm::mat4 model = glm::mat4(1.0f);
        //GLM 的 translate/rotate/scale 会把新变换乘在传入矩阵的右边，所以代码这样写：
        // glm::mat4 model(1.0f);
        // model = glm::translate(model, position);                  // T
        // model = glm::rotate(model, angle, glm::vec3(0, 0, 1));    // T * R
        // model = glm::scale(model, glm::vec3(size, 1.0f));          // T * R * S
        //这样作用的时候就是S然后R再是T
        model = glm::translate(model,position);
        model = glm::rotate(model,glm::radians(angle),glm::vec3(0.0f,0.0f,1.0f));
        model = glm::scale(model,glm::vec3(size,1.0f));
        shader->SetMat4("ModelMatrix",model);
        s_Render2D_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Render2D_Data->QuadVertexArray);

    }

    void Renderer2D::Flush(){
        auto& data = *s_Render2D_Data;

        if (data.QuadIndexCount == 0){
            return;
        }


        Ref<Shader> shader = data.QuadShaders->Get("quadShader");
        shader->Bind();

        uint32_t vertexCount = static_cast<uint32_t>(data.QuadVertexBufferPtr-data.QuadVertexBufferBase);
        uint32_t vertexSize = vertexCount*sizeof(QuadVertex);

        data.QuadVertexBuffer->SetData(data.QuadVertexBufferBase,vertexSize);
        RenderCommand::DrawIndexed(data.QuadVertexArray,data.QuadIndexCount);
    }

    void Renderer2D::EndScene(){
       Flush();
    }
}
