#include "Renderer.h"
#include "RenderCommand.h"

namespace Carrot
{

    Renderer::SceneData* Renderer::s_SceneData = new SceneData();

    void Renderer::BeginScene(OrthographicCamera& camera){
       s_SceneData->ProjectionViewMatrix = camera.GetProjectionViewMatrix();
    }

    void Renderer::EndScene(){

    }

    void Renderer::Submit(
            const Material& material,
            std::shared_ptr<VertexArray> vao,
            const glm::mat4 model
        ){
        const auto& shader = material.GetShader();
        shader->Bind();
        shader->SetMat4("ProjectionViewMatrix",s_SceneData->ProjectionViewMatrix);
        shader->SetMat4("ModelMatrix",model);
        shader->SetFloat4("u_Color", material.GetColor());
        RenderCommand::DrawIndexed(vao);
    }

}