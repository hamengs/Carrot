#pragma once

#include "Core/Core.h"

#include <glm/glm.hpp>

#include <memory>

namespace Carrot
{
    class VertexArray;
    //抽象类,对于不同的Renderer,比如opengl,vulkan,需要实现不同的派生类
    class RendererAPI{
    public: 
        enum class API{
            None = 0, OpenGL = 1
        };
        virtual void Init() = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;
        virtual void DrawIndexed(const Ref<VertexArray> vao) = 0;
        virtual void DrawIndexed(const Ref<VertexArray> vao, uint32_t indexCount = 0) = 0;
        virtual void SetViewport(uint32_t width, uint32_t height) = 0;
        //返回实际使用的api
        inline static API GetAPI(){return api;}
        static RendererAPI* Create();
    private:
        static API api;
    };
}

