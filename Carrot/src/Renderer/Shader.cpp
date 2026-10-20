#include "Shader.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <stdexcept>


namespace Carrot
{
    std::shared_ptr<Shader> Shader::Create(
        const std::string& vertexSrc,
        const std::string& fragmentSrc
    ) {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLShader>(
                    vertexSrc, fragmentSrc
                );

            default:
                throw std::runtime_error(
                    "Unsupported renderer API for Shader"
                );
        }
    }
}