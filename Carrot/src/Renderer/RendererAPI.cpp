#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include <stdexcept>

namespace Carrot{
    //具体API改变可以放在这
    RendererAPI::API RendererAPI::api = RendererAPI::API::OpenGL;

    RendererAPI* RendererAPI::Create(){
        switch (RendererAPI::GetAPI())
        {
        case RendererAPI::API::None:
            return nullptr;
            break;
        case RendererAPI::API::OpenGL:
            return new OpenGLRendererAPI();
        }
        throw std::runtime_error("Unknown renderer API");
    }
}