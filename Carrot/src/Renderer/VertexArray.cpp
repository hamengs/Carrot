#include "Renderer/VertexArray.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer/Renderer.h"

namespace Carrot
{
    //同样的根据不同的api创建不同的api对象
    Ref<VertexArray> VertexArray::Create(){
        switch(Renderer::GetAPI()){
            case RendererAPI::API::None:
                return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLVertexArray>();
        }
        throw std::invalid_argument("Unknown RendererAPI");
    }

}
