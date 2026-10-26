#include "Renderer/Buffer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer/Renderer.h"

//使用static工厂来决定创建的到底是哪个渲染api
namespace Carrot
{
    VertexBuffer* VertexBuffer::Create(uint32_t size){
        switch(Renderer::GetAPI()){
            case RendererAPI::API::None:
                return nullptr;
            case RendererAPI::API::OpenGL:
                return new OpenGLVertexBuffer(size);
        }
        throw std::runtime_error("Unknown RendererAPI");
    }

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size){
        switch(Renderer::GetAPI()){
            case RendererAPI::API::None:
                return nullptr;
            case RendererAPI::API::OpenGL:
                return new OpenGLVertexBuffer(vertices,size);
        }
        throw std::runtime_error("Unknown RendererAPI");
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size){
        switch(Renderer::GetAPI()){
            case RendererAPI::API::None:
                return nullptr;
            case RendererAPI::API::OpenGL:
                return new OpenGLIndexBuffer(indices,size);
        }
        throw std::invalid_argument("Unknown ShaderDataType");
    }
}