#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"
#include <stdexcept>

namespace Carrot{
    Ref<Texture2D> Texture2D::Create(const std::string& path){
        switch(Renderer::GetAPI()){
            case RendererAPI::API::None:
                return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLTexture2D>(path);
        }
        throw std::invalid_argument("Unknown RendererAPI");
    }
}