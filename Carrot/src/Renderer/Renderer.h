#pragma once

namespace Carrot
{
    //配置文件,编译时可以改变渲染api
    enum class RendererAPI{
        None = 0, OpenGL = 1
    };

    class Renderer{
    public:
        inline static RendererAPI GetAPI(){return s_RendererAPI;}
    private:
        static RendererAPI s_RendererAPI;
    };
} // namespace Carrot
