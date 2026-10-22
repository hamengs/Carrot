#include "Renderer/Texture.h"

namespace Carrot
{
    class OpenGLTexture2D : public Texture2D{
    public:
        OpenGLTexture2D(const std::string& m_Path);
        virtual ~OpenGLTexture2D();
        virtual void Bind(uint32_t slot) const override;
        virtual inline uint32_t GetWidth() const override{return m_Width;}
        virtual inline uint32_t GetHeight() const override{return m_Height;}
        virtual inline uint32_t GetChannel() const override{return m_Channel;}
    private:
        const std::string& m_Path;
        uint32_t m_Width;
        uint32_t m_Height;
        uint32_t m_Channel;
        uint32_t m_Texture2D_ID;
    };
}