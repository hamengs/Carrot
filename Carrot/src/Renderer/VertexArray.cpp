#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Carrot
{
    //同样的根据不同的api创建不同的api对象
    VertexArray* VertexArray::Create(){
        switch(Renderer::GetAPI()){
            case RendererAPI::None:
                return nullptr;
            case RendererAPI::OpenGL:
                return new OpenGLVertexArray();
        }
        throw std::invalid_argument("Unknown RendererAPI");
    }

}
