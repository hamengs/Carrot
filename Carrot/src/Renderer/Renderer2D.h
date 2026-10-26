#pragma once

#include "Core/Core.h"
#include <glm/glm.hpp>
#include "Renderer/OrthographicCameraController.h"
#include "Renderer/Material.h"

namespace Carrot{

    //绘制2d相关内容在这里,就是绘制一个quad,写死了shader和顶点
    class Renderer2D{
    public:
        static void Init();
        static void ShunDown();
        static void BeginScene(const OrthographicCamera& camera);
        static void OnWindowResize(uint32_t width, uint32_t height);
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const float& angle, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const float& angle, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4 tintColor);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const float& angle, const Ref<Texture2D>& texture, const glm::vec4 tintColor);
        static void EndScene();
    private:
        static void StartBatch();
        static void Flush();
    };
}