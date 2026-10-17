#pragma once

#include "Core.h"
#include <cstdint>
#include <string>
#include <vector>
#include <initializer_list>
#include <stdexcept>

//把vsb和index抽象出来,作为纯虚函数
namespace Carrot{

    //对于不同的顶点属性类型定义不同的顶点属性
    enum ShaderDataType{
        FLOAT = 0, FLOAT2, FLOAT3, FLOAT4, MAT2, MAT3, MAT4, INT, INT2, INT3, INT4, BOOL
    };

    //返回顶点属性的字节大小,一个float是4个字节,一个int也是
    static uint32_t GetShaderDataTypeSize(ShaderDataType type){
        switch(type){
            case ShaderDataType::FLOAT  : return 4;
            case ShaderDataType::FLOAT2 : return 2*4;
            case ShaderDataType::FLOAT3 : return 3*4;
            case ShaderDataType::FLOAT4 : return 4*4;
            case ShaderDataType::MAT2   : return 2*2*4;
            case ShaderDataType::MAT3   : return 3*3*4;
            case ShaderDataType::MAT4   : return 4*4*4;
            case ShaderDataType::INT    : return 4;
            case ShaderDataType::INT2   : return 2*4;
            case ShaderDataType::INT3   : return 3*4;
            case ShaderDataType::INT4   : return 4*4;
            case ShaderDataType::BOOL   : return 1;
        }
        throw std::invalid_argument("Unknown ShaderDataType");
    }

    //顶点属性,举例 layout (location = 0) vec3 a_Pos;
    struct BufferElement{

        BufferElement() = default;
        BufferElement(
            ShaderDataType type,
            std::string name):
                Name(name),
                Type(type),
                Size(GetShaderDataTypeSize(type)),
                Offset(0),
                Normalized(false){

            }

        std::string Name;
        ShaderDataType Type;
        //size值得是一个元素的大小,比如一个Pos应该是3个float,也就是3(个float)*4(每个float4个字节),而不是所有Pos的集合大小
        uint32_t Size;
        //该元素在被指定分布时的offset
        uint32_t Offset;
        bool Normalized;

        //顶点属性的数量,一个顶点属性比如Pos有三个数xyz,颜色rgba,float1,2,3代表float有几个
        uint32_t GetElementCount() const {
            switch(Type){
                case ShaderDataType::FLOAT  : return 1;
                case ShaderDataType::FLOAT2 : return 2;
                case ShaderDataType::FLOAT3 : return 3;
                case ShaderDataType::FLOAT4 : return 4;
                case ShaderDataType::MAT2   : return 2*2;
                case ShaderDataType::MAT3   : return 3*3;
                case ShaderDataType::MAT4   : return 4*4;
                case ShaderDataType::INT    : return 1;
                case ShaderDataType::INT2   : return 2;
                case ShaderDataType::INT3   : return 3;
                case ShaderDataType::INT4   : return 4;
                case ShaderDataType::BOOL   : return 1;
            }
            throw std::invalid_argument("Unknown ShaderDataType");
        }
    };

    //顶点属性分布 举例:
    //layout (location = 0) vec3 a_Pos;
    //layout (location = 1) vec4 a_Color;
    //上面两个顶点属性组成了一个顶点布局
    class BufferLayout{
    public:
        BufferLayout() = default;
        BufferLayout(std::initializer_list<BufferElement> elements):m_Elements(elements){
            CalculateOffsetsAndStride();
        }

        const inline std::vector<BufferElement>& GetElements() const {return m_Elements;}
        inline uint32_t GetStride() const {return m_Stride;}

        //两个迭代器,一个是const,一个是普通,这样子可以通过for(auto :)来访问,同时const保证需要只读访问的时候也能调用
        std::vector<BufferElement>::iterator begin(){return m_Elements.begin();}
        std::vector<BufferElement>::iterator end(){return m_Elements.end();}
        std::vector<BufferElement>::const_iterator begin() const{return m_Elements.begin();}
        std::vector<BufferElement>::const_iterator end()const {return m_Elements.end();}


    private:
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride = 0;

        //计算vaoAttrib的步长和偏移
        void CalculateOffsetsAndStride(){
            uint32_t offset = 0;
            for(BufferElement& element : m_Elements){
                element.Offset = offset;
                offset += element.Size;

            }
            m_Stride = offset;
        }
    };

    class VertexBuffer{
    public:
        virtual ~VertexBuffer() = default;
        virtual void Bind() = 0;
        virtual void UnBind() = 0;
        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& GetLayout() const = 0;

        static VertexBuffer* Create(float* vertices, uint32_t size);
    };

    class IndexBuffer{
    public:
        virtual ~IndexBuffer() = default;
        virtual void Bind() = 0;
        virtual void UnBind() = 0;
        virtual uint32_t GetCount() = 0;

        static IndexBuffer* Create(uint32_t* indices, uint32_t size);

    };
}