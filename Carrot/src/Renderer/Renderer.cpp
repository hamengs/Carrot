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

    void Renderer::Submit(std::shared_ptr<Shader> shader, std::shared_ptr<VertexArray> vao){
        shader->Bind();
        shader->UploadUniformMat4f("ProjectionViewMatrix",s_SceneData->ProjectionViewMatrix);
        RenderCommand::DrawIndexed(vao);
    }

}