#include "Renderer/Texture.h"

#include "Platform/OpenGL/OpenGLTexture2D.h"
#include "Renderer/Renderer.h"

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

    Ref<Texture2D> Texture2D::Create(const uint32_t width, const uint32_t height){
        switch(Renderer::GetAPI()){
            case RendererAPI::API::None:
                return nullptr;
            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLTexture2D>(width,height);
        }
        throw std::invalid_argument("Unknown RendererAPI");
    }
}