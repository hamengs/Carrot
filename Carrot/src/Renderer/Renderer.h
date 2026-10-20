#pragma once

#include "RendererAPI.h"
#include <memory>
#include "Renderer/OrthographicCamera.h"
#include "Renderer/Shader.h"
#include "Renderer/Material.h"

namespace Carrot
{
    //顶层绘画类负责调用底层RenderCommand
    class Renderer{
    public:
        static void BeginScene(OrthographicCamera& camera);
        static void Submit(
                const Material& material,
                const std::shared_ptr<VertexArray> vao,
                const glm::mat4 model = glm::mat4(1.0f)
            );
        static void EndScene();
        inline static RendererAPI::API GetAPI(){return RendererAPI::GetAPI();}

    private:
        struct SceneData{
            glm::mat4 ProjectionViewMatrix;
        };

        static SceneData* s_SceneData;
    };
} // namespace Carrot
