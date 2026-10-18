#include "Renderer.h"
#include "RenderCommand.h"

namespace Carrot
{
    void Renderer::BeginScene(){

    }

    void Renderer::EndScene(){

    }

    void Renderer::Submit(std::shared_ptr<VertexArray> vao){
        RenderCommand::DrawIndexed(vao);
    }

}