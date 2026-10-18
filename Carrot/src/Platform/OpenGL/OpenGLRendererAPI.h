#pragma once

#include "Renderer/RendererAPI.h"

namespace Carrot{
    //OpenGL渲染相关指令
    class OpenGLRendererAPI : public RendererAPI{
    public:

        virtual void SetClearColor(const glm::vec4& color)override;
        virtual void Clear() override;
        virtual void DrawIndexed(const std::shared_ptr<VertexArray> vao) override;

    };
}
