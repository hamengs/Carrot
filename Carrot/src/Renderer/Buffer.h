#pragma once

#include "Core.h"
#include <cstdint>

namespace Carrot{
    class VertexBuffer{
    public:
        virtual ~VertexBuffer() = default;
        virtual void Bind() = 0;
        virtual void UnBind() = 0;

        static VertexBuffer* Create(float* vertices, uint32_t size);
    };
    
    class IndexBuffer{
    public:
        virtual ~IndexBuffer() = default;
        virtual void Bind() = 0;
        virtual void UnBind() = 0;

        static IndexBuffer* Create(uint32_t* indices, uint32_t size);

    };
}