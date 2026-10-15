#pragma once

#include "Core.h"
#include "Renderer/Buffer.h"

namespace Carrot
{
    class OpenGLVertexBuffer : public VertexBuffer{
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer() override;
        virtual void Bind() override;
        virtual void UnBind() override;
        inline uint32_t GetSize(){return m_Size;}

    private:
        uint32_t m_VertexID;
        uint32_t m_Size;
    };
    
    class OpenGLIndexBuffer : public IndexBuffer{
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
        virtual ~OpenGLIndexBuffer() override;
        virtual void Bind() override;
        virtual void UnBind() override;
        inline uint32_t GetCount(){return m_Count;}

    private:
        uint32_t m_IndexID;
        uint32_t m_Count; //计数有时候有特别用处,可以在这里统计
    };
}