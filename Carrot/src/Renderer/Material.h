#pragma once

#include "Shader.h"
#include <utility>

namespace Carrot
{
    class Material{
    public:
    //创建时不使用引用,因为外部shader销毁的情况下,材质系统依然可以保留一份自己的有效shader
    //std::move在这里是因为外部传入一个shader,构造函数的参数复制持有这个shader,然后std::move移动的是构造函数的参数所复制的shader,然后转移给m_Shader
        explicit Material(std::shared_ptr<Shader> shader):m_Shader(std::move(shader)){

        }

        void SetColor(const glm::vec4& color){m_Color = color;}

        glm::vec4 GetColor() const {return m_Color;}
        const std::shared_ptr<Shader>& GetShader() const{return m_Shader;}

    private:
        std::shared_ptr<Shader> m_Shader;
        glm::vec4 m_Color{1.0f};
    };
}