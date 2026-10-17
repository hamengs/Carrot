#include "OpenGLBuffer.h"
#include <glad/glad.h>

//这里就是真正调用底层api的地方
namespace Carrot
{   

    //----------------------VBO----------------------------
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size): m_Size(size){
        glCreateBuffers(1,&m_VertexID);
        glBindBuffer(GL_ARRAY_BUFFER,m_VertexID);
        glBufferData(GL_ARRAY_BUFFER,m_Size,vertices,GL_STATIC_DRAW); 
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer(){
        glDeleteBuffers(1,&m_VertexID);
    }

    void OpenGLVertexBuffer::Bind(){
        glBindBuffer(GL_ARRAY_BUFFER,m_VertexID);
    }

   void OpenGLVertexBuffer::UnBind(){
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }

    void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout){
            m_Layout = layout;
    }

    //----------------------IndexBuffer-------------------------------------
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t size): m_Count(size/sizeof(uint32_t)){
        glCreateBuffers(1,&m_IndexID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_IndexID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,size,indices,GL_STATIC_DRAW); 
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer(){
        glDeleteBuffers(1,&m_IndexID);
    }

    void OpenGLIndexBuffer::Bind(){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_IndexID);
    }

    void OpenGLIndexBuffer::UnBind(){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    }

} 
