#pragma once

#include "RendererAPI.h"
#include <memory>

namespace Carrot
{
    //顶层绘画类负责调用底层RenderCommand
    class Renderer{
    public:
        static void BeginScene();
        static void Submit(std::shared_ptr<VertexArray> vao);
        static void EndScene();
        inline static RendererAPI::API GetAPI(){return RendererAPI::GetAPI();}
    };
} // namespace Carrot
