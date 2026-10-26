#pragma once

#include "Core/Core.h"
#include "Renderer/Buffer.h"

#include <memory>

namespace Carrot
{

    class OpenGLVertexBuffer : public VertexBuffer{
    public:
        OpenGLVertexBuffer(uint32_t size);
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer() override;
        virtual void Bind() override;
        virtual void UnBind() override;
        inline uint32_t GetSize(){return m_Size;}
        virtual void SetLayout(const BufferLayout& layout) override;
        virtual inline const BufferLayout& GetLayout() const override{return m_Layout;}
        virtual void SetData(const void* data, uint32_t size) override;
    private:
        //vbo的布局描述
        BufferLayout m_Layout;
        uint32_t m_VertexID;
        uint32_t m_Size;

    };

    class OpenGLIndexBuffer : public IndexBuffer{
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
        virtual ~OpenGLIndexBuffer() override;
        virtual void Bind() override;
        virtual void UnBind() override;
        virtual inline uint32_t GetCount() override{return m_Count;}

    private:
        uint32_t m_IndexID;
        uint32_t m_Count; //计数有时候有特别用处,可以在这里统计
    };
}