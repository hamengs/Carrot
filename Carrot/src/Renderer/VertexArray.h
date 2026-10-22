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
            const Ref<VertexBuffer>& vertexBuffer) = 0;

        virtual void SetIndexBuffer(
            const Ref<IndexBuffer>& indexBuffer) = 0;

        
        virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;


        virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
    };


}
