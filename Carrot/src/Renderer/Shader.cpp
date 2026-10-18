#include "Shader.h"
#include <glad/glad.h>
#include "Log.h"
#include <vector>

namespace Carrot
{
    Shader::Shader(const std::string& vertexStringSrc, const std::string& fragmentStringSrc){
        const GLchar* vertexSrc = vertexStringSrc.c_str();
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
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

        const GLchar* fragSrc = fragmentStringSrc.c_str();
        GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragShader, 1, &fragSrc, nullptr);
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

    void Shader::Bind(){
        glUseProgram(m_ShaderID);
    }

    void Shader::UnBind(){
        glUseProgram(0);
    }
}