#pragma once

#include "Core/Core.h"

#include <glm/glm.hpp>

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

namespace Carrot
{
    class Shader{
    public:
        virtual ~Shader() = default;

        virtual void Bind() const  = 0;
        virtual void UnBind() const  = 0;

        // 设置参数前先 Bind()；数组 count 表示元素个数，不是字节数。
        virtual void SetInt(const std::string& name, int value) = 0;
        virtual void SetIntArray(const std::string& name, const int* values, uint32_t count) = 0;
        virtual void SetFloat(const std::string& name, float value) = 0;
        virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
        virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
        virtual void SetMat3(const std::string& name, const glm::mat3& value) = 0;

        virtual void SetMat4(
            const std::string& name,
            const glm::mat4& value
        ) = 0;

        virtual void SetFloat4(
            const std::string& name,
            const glm::vec4& value
        ) = 0;
        //创建时必须明确名字
        static Ref<Shader> Create(
            const std::string& name,   
            const std::string& vertexSrc,
            const std::string& fragmentSrc
        );
        
    };

    class ShaderLibrary{
    public:
        //使用一个library来做到shader可复用
        void Add(const std::string& name, const Ref<Shader>& shader);
        //直接加载路径来加载Shader
        Ref<Shader> Load(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
        Ref<Shader> Load( const std::string& vertexPath, const std::string& fragmentPath);
        Ref<Shader> Get(const std::string& name);

    private:
        //使用hashmap来存储已经有的shaders
        std::unordered_map<std::string,Ref<Shader>> m_Shaders;
    };
}
