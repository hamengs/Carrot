#pragma once

#include "Renderer/VertexArray.h"

namespace Carrot
{
    class OpenGLVertexArray : public VertexArray{
        public:
            OpenGLVertexArray();
            virtual ~OpenGLVertexArray() override;
            virtual void Bind() override;
            virtual void UnBind() override;
            virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
            virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
            inline uint32_t GetVertexArrayID(){return m_VertexArrayID;}
            virtual inline const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override{return m_VertexBuffers;}
            virtual inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override{return m_IndexBuffer;}
        private:
        //VAO应该拥有VBO和EBO顶层拥有下层,下层不可以拥有上层,避免循环调用的高耦合
            uint32_t m_VertexArrayID;
            std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
            std::shared_ptr<IndexBuffer> m_IndexBuffer;
            uint32_t m_VertexAttribIndex = 0;

    };


}
