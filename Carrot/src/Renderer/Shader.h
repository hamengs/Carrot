#pragma once

#include <cstdint>
#include <string>
#include <glm/glm.hpp>

namespace Carrot
{
    class Shader{
    public:
        Shader(const std::string& vertexStringSrc, const std::string& fragmentStringSrc);
        ~Shader() = default;

        void Bind();
        void UnBind();

        void UploadUniformMat4f(const std::string& name, const glm::mat4& matrix);

    private:
        uint32_t m_ShaderID = 0;
    };
}