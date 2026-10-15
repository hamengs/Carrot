#pragma once

#include "Core.h"

namespace Carrot
{
    class RenderContext{
    public:
        RenderContext() = default;
        virtual ~RenderContext() = default;

        virtual void Init() = 0;
        virtual void SwapBuffer() = 0;

    };
}