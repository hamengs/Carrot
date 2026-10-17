#include "Buffer.h"
#include "CarrotPCH.h"
#include "Renderer.h"
#include "platform/OpenGL/OpenGLBuffer.h"

//使用static工厂来决定创建的到底是哪个渲染api
namespace Carrot
{
    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size){
        switch(Renderer::GetAPI()){
            case RendererAPI::None:
                return nullptr;
            case RendererAPI::OpenGL:
                return new OpenGLVertexBuffer(vertices,size);
        }
        throw std::runtime_error("Unknown RendererAPI");
        return 0;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size){
        switch(Renderer::GetAPI()){
            case RendererAPI::None:
                return nullptr;
            case RendererAPI::OpenGL:
                return new OpenGLIndexBuffer(indices,size);
        }
        throw std::invalid_argument("Unknown ShaderDataType");
        return 0;
    }
}