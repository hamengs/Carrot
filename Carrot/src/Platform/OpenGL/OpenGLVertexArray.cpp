#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace Carrot
{
    static GLenum GetShaderDataType(ShaderDataType type){
        switch(type){
            case ShaderDataType::FLOAT  : return GL_FLOAT;
            case ShaderDataType::FLOAT2 : return GL_FLOAT;
            case ShaderDataType::FLOAT3 : return GL_FLOAT;
            case ShaderDataType::FLOAT4 : return GL_FLOAT;
            case ShaderDataType::MAT2   : return GL_FLOAT;
            case ShaderDataType::MAT3   : return GL_FLOAT;
            case ShaderDataType::MAT4   : return GL_FLOAT;
            case ShaderDataType::INT    : return GL_INT;
            case ShaderDataType::INT2   : return GL_INT;
            case ShaderDataType::INT3   : return GL_INT;
            case ShaderDataType::INT4   : return GL_INT;
            case ShaderDataType::BOOL   : return GL_BOOL;
        }
        throw std::invalid_argument("Unknown type");
    }

    OpenGLVertexArray::OpenGLVertexArray(){
        glCreateVertexArrays(1,&m_VertexArrayID);
        glBindVertexArray(m_VertexArrayID);
    }

    OpenGLVertexArray::~OpenGLVertexArray(){
        glDeleteVertexArrays(1,&m_VertexArrayID);
    }

    void OpenGLVertexArray::Bind(){
        glBindVertexArray(m_VertexArrayID);
    }

   void OpenGLVertexArray::UnBind(){
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer){
        Bind(); //绑定VAO
        vertexBuffer->Bind();//绑定VBO
        m_VertexBuffers.push_back(vertexBuffer); //把VBO入数组

        //vbo拥有layout,因为启用和设置顶点属性需要vao,所以设置顶点属性的职责需要在vao类内的方法完成.
        for(const BufferElement& element : vertexBuffer->GetLayout()){ 
            glVertexAttribPointer(
                m_VertexAttribIndex,
                element.GetElementCount(),
                GetShaderDataType(element.Type),
                element.Normalized?GL_TRUE:GL_FALSE,
                vertexBuffer->GetLayout().GetStride(),
                //64 位平台上会有整数到指针大小不一致
                reinterpret_cast<const void*>(
                    static_cast<std::uintptr_t>(element.Offset)
                )
            );
        glEnableVertexArrayAttrib(GetVertexArrayID(),m_VertexAttribIndex);
        m_VertexAttribIndex++;
        }
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer){
        Bind();
        m_IndexBuffer = indexBuffer;
        indexBuffer->Bind();
    }


}
