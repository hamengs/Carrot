#include "Platform/OpenGL/OpenGLTexture2D.h"

#include "Core/Log.h"
#include "Profiler/Profiler.h"


#include <stb_image.h>

namespace Carrot
{
    OpenGLTexture2D::OpenGLTexture2D(const uint32_t width, const uint32_t height){
        PROFILER_FUNCTION();
        glCreateTextures(GL_TEXTURE_2D,1,&m_Texture2D_ID);
        glBindTexture(GL_TEXTURE_2D, m_Texture2D_ID);
        m_Width = width;
        m_Height = height;
        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;
        m_Channel = 4;
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
  
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path):m_Path(path){
        PROFILER_SCOPE(path);
        int width,height,channels;
        stbi_set_flip_vertically_on_load(1);
        unsigned char* data = stbi_load(path.c_str(),&width,&height,&channels,0);
        m_Width = width;
        m_Height = height;
        m_Channel = channels;

        glCreateTextures(GL_TEXTURE_2D,1,&m_Texture2D_ID);
        glBindTexture(GL_TEXTURE_2D, m_Texture2D_ID);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        GLenum internalFormat = 0, dataFormat = 0;
        if(channels==4){
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }else if(channels == 3){
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        //前一个rgba是存储为rgba,后一个是读取的格式按照rgba来读取,并且存储为unsignedbyte
        if(data){
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }else{
            CT_CORE_ERROR("Failed to Load texture");
        }

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D(){
        PROFILER_FUNCTION();
        glDeleteTextures(1,&m_Texture2D_ID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const {
        glBindTextureUnit(slot,m_Texture2D_ID);
    }

    void OpenGLTexture2D::SetData(const void* data, uint32_t size) const {
        PROFILER_FUNCTION();
        CT_CORE_ASSERT(size==m_Width*m_Height*4,"Texture data size mismatch");
        glBindTexture(GL_TEXTURE_2D,m_Texture2D_ID);
        glTexImage2D(GL_TEXTURE_2D,0,m_InternalFormat,m_Width,m_Height,0,m_DataFormat,GL_UNSIGNED_BYTE,data);
    }

}
