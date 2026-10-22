#pragma once

#include "Renderer/RendererAPI.h"

namespace Carrot{
    //RenderCommand包含了各种稍微实际的绘制指令,通过持有的s_RendererAPI指针来调用不同rendererAPI的绘制指令
    class RenderCommand{
    public:
        inline static void Init(){
            s_RendererAPI->Init();
        }

        inline static void SetClearColor(const glm::vec4& color){
            s_RendererAPI->SetClearColor(color);
        }

        inline static void Clear(){
            s_RendererAPI->Clear();
        }

        inline static void DrawIndexed(const Ref<VertexArray>& vao){
            s_RendererAPI->DrawIndexed(vao);
        }

        inline static void SetViewport(uint32_t width, uint32_t height){
            s_RendererAPI->SetViewport(width,height);
        }

        inline static RendererAPI* GetRenderAPI(){return s_RendererAPI;}

    private:
        //RendererAPI虽然是一个纯虚类,但是可以通过指针来创建它,因为指针只是一个指向地址的指针不包含实际对象
        //实际确立是哪个api通过cpp的new来确定
        static RendererAPI* s_RendererAPI;
    };
}
