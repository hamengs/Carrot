#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include "Log.h"
#include <vector>
#include <limits>
#include <stdexcept>

namespace Carrot
{
    OpenGLShader::~OpenGLShader()
    {
        if (m_ShaderID != 0)
            glDeleteProgram(m_ShaderID);
    }

    void OpenGLShader::Bind() const {
        glUseProgram(m_ShaderID);
    }

    void OpenGLShader::UnBind() const{
        glUseProgram(0);
    }

    void OpenGLShader::SetInt(const std::string& name, int value)
    {
        const GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::SetIntArray(
        const std::string& name, const int* values, uint32_t count
    ) {
        if (count == 0)
            return;
        if (values == nullptr)
            throw std::invalid_argument("SetIntArray requires non-null values when count is positive");
        if (count > static_cast<uint32_t>((std::numeric_limits<GLsizei>::max)()))
            throw std::out_of_range("SetIntArray count exceeds GLsizei range");

        const GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
        glUniform1iv(location, static_cast<GLsizei>(count), values);
    }

    void OpenGLShader::SetFloat(const std::string& name, float value)
    {
        const GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
    {
        const GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
        glUniform2fv(location, 1, glm::value_ptr(value));
    }

    void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
    {
        const GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
        glUniform3fv(location, 1, glm::value_ptr(value));
    }

    void OpenGLShader::SetMat3(const std::string& name, const glm::mat3& value)
    {
        const GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
    }

    void OpenGLShader::SetMat4(
        const std::string& name,
        const glm::mat4& value
    ){
        const GLint location =
            glGetUniformLocation(m_ShaderID, name.c_str());

        glUniformMatrix4fv(
            location, 1, GL_FALSE, glm::value_ptr(value)
        );
    }

    void OpenGLShader::SetFloat4(
        const std::string& name,
        const glm::vec4& value
    ) {
        const GLint location =
            glGetUniformLocation(m_ShaderID, name.c_str());

        glUniform4fv(location, 1, glm::value_ptr(value));
    }

    OpenGLShader::OpenGLShader(
        const std::string& name,
        const std::string& vertexSrc,
        const std::string& fragmentSrc
    ):m_Name(name){
        const GLchar* vertexSource = vertexSrc.c_str();
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertexShader, 1, &vertexSource, nullptr);
        glCompileShader(vertexShader);

        GLint success = GL_FALSE;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

        if (success != GL_TRUE)
        {
            GLint length = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);

            std::vector<GLchar> log(length > 0 ? length : 1);
            glGetShaderInfoLog(
                vertexShader,
                static_cast<GLsizei>(log.size()),
                nullptr,
                log.data()
            );

            CT_CORE_ERROR("Vertex shader compilation failed:\n{}", log.data());

            glDeleteShader(vertexShader);
            return;

        }

        const GLchar* fragmentSource = fragmentSrc.c_str();
        GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragShader, 1, &fragmentSource, nullptr);
        glCompileShader(fragShader);


        glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);

        if (success != GL_TRUE)
        {
            GLint length = 0;
            glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &length);

            std::vector<GLchar> log(length > 0 ? length : 1);
            glGetShaderInfoLog(
                fragShader,
                static_cast<GLsizei>(log.size()),
                nullptr,
                log.data()
            );

            CT_CORE_ERROR("Fragment shader compilation failed:\n{}", log.data());

            glDeleteShader(fragShader);
            glDeleteShader(vertexShader);
            return;;
        }


        // 3. 创建 program，把两个 shader 添加进去
        GLuint program = glCreateProgram();

        if (program == 0)
        {
            glDeleteShader(vertexShader);
            glDeleteShader(fragShader);
            return;
        }

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragShader);

        // 4. 链接
        glLinkProgram(program);

        // 注意：检查链接用 glGetProgramiv，不是 glGetShaderiv
        glGetProgramiv(program, GL_LINK_STATUS, &success);

        if (success != GL_TRUE)
        {
            GLint length = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

            std::vector<GLchar> log(length > 0 ? length : 1);
            glGetProgramInfoLog(
                program,
                static_cast<GLsizei>(log.size()),
                nullptr,
                log.data()
            );

            CT_CORE_ERROR("Shader program linking failed:\n{}", log.data());
        }

        // 5. 链接完成后，可以释放独立的 shader 对象
        // 成功链接的 program 仍然可以正常使用
        glDetachShader(program, vertexShader);
        glDetachShader(program, fragShader);
        glDeleteShader(vertexShader);
        glDeleteShader(fragShader);

        if (success != GL_TRUE)
        {
            glDeleteProgram(program);
            return;
        }

        m_ShaderID = program;
    }
}
