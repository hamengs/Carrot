#include "Shader.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <stdexcept>
#include <filesystem>
#include "File.h"

namespace Carrot
{

    Ref<Shader> Shader::Create(
        const std::string& name,   
        const std::string& vertexSrc,
        const std::string& fragmentSrc
    ) {
        switch (RendererAPI::GetAPI())
        {
            case RendererAPI::API::OpenGL:
                return std::make_shared<OpenGLShader>(
                    name, vertexSrc, fragmentSrc
                );

            default:
                throw std::runtime_error(
                    "Unsupported renderer API for Shader"
                );
        }
    }

    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader){
        auto it = m_Shaders.find(name);
        CT_CORE_ASSERT(it==m_Shaders.end(),"Shader already exists!");
        m_Shaders[name] = shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath){
        auto it = m_Shaders.find(name);
        CT_CORE_ASSERT(it==m_Shaders.end(),"Shader already exists!");

        auto vertexSrc = File::ReadFile(vertexPath);
        auto fragmentSrc = File::ReadFile(fragmentPath);

        auto shader = Shader::Create(name,vertexSrc,fragmentSrc);
        m_Shaders[name] = shader;
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& vertexPath, const std::string& fragmentPath){
        //stem去掉扩展名和/或者\前面的路径
        auto name = std::filesystem::path(vertexPath).stem().string();
        auto it = m_Shaders.find(name);
        CT_CORE_ASSERT(it==m_Shaders.end(),"Shader already exists!");

        auto vertexSrc = File::ReadFile(vertexPath);
        auto fragmentSrc = File::ReadFile(fragmentPath);

        auto shader = Shader::Create(name,vertexSrc,fragmentSrc);
        m_Shaders[name] = shader;
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string& name){
        auto it = m_Shaders.find(name);
        CT_CORE_ASSERT(it!=m_Shaders.end(),"Shader does not exist");
        //m_Shaders[name] 会在上面失败的时候偷偷插入一个空指针,所以写成.at(name);
        return m_Shaders.at(name);
    }
}