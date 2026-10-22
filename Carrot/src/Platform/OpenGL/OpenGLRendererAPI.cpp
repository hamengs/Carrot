#include "OpenGLRendererAPI.h"
#include "Renderer/VertexArray.h"
#include <glad/glad.h>

namespace Carrot{
    
    void OpenGLRendererAPI::Init(){
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color){
        glClearColor(color.r,color.g,color.b,color.a);
    }

    void OpenGLRendererAPI::Clear(){
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray> vao){
        vao->Bind();
        glDrawElements(GL_TRIANGLES,vao->GetIndexBuffer()->GetCount(),GL_UNSIGNED_INT,nullptr);
    }

    void OpenGLRendererAPI::SetViewport(uint32_t width, uint32_t height){
        glViewport(0,0,width,height);
    }

}
