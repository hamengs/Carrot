#include "Renderer/Texture.h"
#include <glad/glad.h>

namespace Carrot
{
    class OpenGLTexture2D : public Texture2D{
    public:
        OpenGLTexture2D(const std::string& m_Path);
        OpenGLTexture2D(const uint32_t width, const uint32_t height);
        virtual ~OpenGLTexture2D();
        virtual void Bind(uint32_t slot) const override;
        virtual inline uint32_t GetWidth() const override{return m_Width;}
        virtual inline uint32_t GetHeight() const override{return m_Height;}
        virtual inline uint32_t GetChannel() const override{return m_Channel;}
        virtual inline void SetData(const void* data, uint32_t size) const override;
    private:
        const std::string m_Path;
        uint32_t m_Width;
        uint32_t m_Height;
        uint32_t m_Channel;
        uint32_t m_Texture2D_ID;
        GLenum m_InternalFormat;
        GLenum m_DataFormat;
    };
}