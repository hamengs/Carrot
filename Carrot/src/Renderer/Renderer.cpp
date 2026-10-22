#include "Renderer.h"
#include "RenderCommand.h"

namespace Carrot
{

    Renderer::SceneData* Renderer::s_SceneData = new SceneData();

    void Renderer::Init(){
        RenderCommand::Init();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height){
        RenderCommand::SetViewport(width, height);
    }

    void Renderer::BeginScene(const OrthographicCamera& camera){
       s_SceneData->ProjectionViewMatrix = camera.GetProjectionViewMatrix();
    }

    void Renderer::EndScene(){

    }

    void Renderer::Submit(
            const Material& material,
            Ref<VertexArray> vao,
            const glm::mat4 model
        ){
        const auto& shader = material.GetShader();
        const auto& texture = material.GetTexture2D();
        shader->Bind();
        texture->Bind(0);
        shader->SetMat4("ProjectionViewMatrix",s_SceneData->ProjectionViewMatrix);
        shader->SetMat4("ModelMatrix",model);
        shader->SetFloat4("u_Color", material.GetColor());
        shader->SetInt("u_Texture",0);
        RenderCommand::DrawIndexed(vao);
    }

}
