#include "Renderer/RenderCommand.h"

namespace Carrot
{
    //在这里s_RendererAPI被真正确立为对应的RendererAPI
    RendererAPI* RenderCommand::s_RendererAPI = RendererAPI::Create();
}