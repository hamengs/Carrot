#pragma once

#include "RendererAPI.h"
#include <memory>
#include "Renderer/OrthographicCamera.h"
#include "Renderer/Shader.h"

namespace Carrot
{
    //顶层绘画类负责调用底层RenderCommand
    class Renderer{
    public:
        static void BeginScene(OrthographicCamera& camera);
        static void Submit(std::shared_ptr<Shader> shader, std::shared_ptr<VertexArray> vao);
        static void EndScene();
        inline static RendererAPI::API GetAPI(){return RendererAPI::GetAPI();}

    private:
        struct SceneData{
            glm::mat4 ProjectionViewMatrix;
        };

        static SceneData* s_SceneData;
    };
} // namespace Carrot
