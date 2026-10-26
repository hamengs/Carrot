#pragma once

#include "Core/Core.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

#include <utility>

namespace Carrot
{
    class Material{
    public:
    //创建时不使用引用,因为外部shader销毁的情况下,材质系统依然可以保留一份自己的有效shader
    //std::move在这里是因为外部传入一个shader,构造函数的参数复制持有这个shader,然后std::move移动的是构造函数的参数所复制的shader,然后转移给m_Shader
        explicit Material(Ref<Shader> shader):m_Shader(std::move(shader)){

        }

        void SetColor(const glm::vec4& color){m_Color = color;}
        //参数里面的texture引用了外部的texture,然后成员变量因为没有&所以把这个引用的texture复制到自己的成员里面了?然后计数+1了,这中间计数+1,没有-1
        void SetTexture2D(const Ref<Texture2D>& texture){m_Texture2D = texture;}
        glm::vec4 GetColor() const {return m_Color;}
        const Ref<Shader>& GetShader() const{return m_Shader;}
        const Ref<Texture2D>& GetTexture2D() const{return m_Texture2D;}

    private:
        Ref<Shader> m_Shader;
        Ref<Texture2D> m_Texture2D;
        glm::vec4 m_Color{1.0f};
    };
}