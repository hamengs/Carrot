#pragma once

#include "Core.h"
#include "string" 

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
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual inline uint32_t GetChannel() const = 0;
        static Ref<Texture2D> Create(const std::string& path );
    };
}