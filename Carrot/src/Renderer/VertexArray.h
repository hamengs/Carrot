#pragma once

#include "Renderer/Buffer.h"
#include <memory>
#include <vector>

namespace Carrot
{
    //抽象出来的VAO
    class VertexArray{
    public:
        virtual ~VertexArray() = default;
        virtual void Bind() = 0;
        virtual void UnBind() = 0;

        static VertexArray* Create();

        //VAO会有VBO和IndexBuffer,所以这里赋予set和get方法
        virtual void AddVertexBuffer(
            const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;

        virtual void SetIndexBuffer(
            const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

        
        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;


        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;
    };


}
