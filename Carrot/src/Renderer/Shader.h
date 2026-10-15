#pragma once

#include "Core.h"
#include "CarrotPCH.h"

namespace Carrot
{
    class Shader{
    public:
        Shader(const std::string& vertexStringSrc, const std::string& fragmentStringSrc);
        ~Shader() = default;

        void Bind();
        void UnBind();

    private:
        uint32_t m_ShaderID = 0;
    };
}