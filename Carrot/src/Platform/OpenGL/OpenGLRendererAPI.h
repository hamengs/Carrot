#pragma once

#include "Renderer/RendererAPI.h"

namespace Carrot{
    //OpenGL渲染相关指令
    class OpenGLRendererAPI : public RendererAPI{
    public:
        virtual void Init() override;
        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;
        virtual void DrawIndexed(const Ref<VertexArray> vao) override;
        virtual void SetViewport(uint32_t width, uint32_t height) override;
    };
}
