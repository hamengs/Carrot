#pragma once

#include "Core/Core.h"
#include "Renderer/Material.h"
#include "Renderer/OrthographicCamera.h"
#include "Renderer/RendererAPI.h"
#include "Renderer/Shader.h"

#include <memory>

namespace Carrot
{
    //顶层绘画类负责调用底层RenderCommand
    class Renderer{
    public:
        static void Init();
        static void BeginScene(const OrthographicCamera& camera);
        static void OnWindowResize(uint32_t width, uint32_t height);
        static void Submit(
                const Material& material,
                const Ref<VertexArray> vao,
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
