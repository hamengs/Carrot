#pragma once

#include "Core/Core.h"

#include <string>

namespace Carrot
{
    class Texture{
    public:
        virtual ~Texture() = default;
        virtual void Bind(uint32_t slot) const = 0;
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual inline uint32_t GetChannel() const = 0;
    };

    class Texture2D : public Texture{
    public:
        virtual ~Texture2D() = default;
        virtual void Bind(uint32_t slot) const = 0;
        //为了传输自定义的纹理
        virtual void SetData(const void* data, uint32_t size) const = 0;
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual inline uint32_t GetChannel() const = 0;
        static Ref<Texture2D> Create(const std::string& path );
        static Ref<Texture2D> Create(const uint32_t width, const uint32_t height);
    };
}