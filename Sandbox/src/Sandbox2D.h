#pragma once

#include "Carrot.h"


class Sandbox2D : public Carrot::Layer {
public:
    Sandbox2D();
    ~Sandbox2D() override = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate() override;
    virtual void OnEvent(Carrot::Event& e) override;
    virtual void OnImGuiRender() override;
private:
    Carrot::Ref<Carrot::ShaderLibrary> m_Shaders;
    Carrot::Ref<Carrot::VertexArray> m_VAO;
    Carrot::Ref<Carrot::Shader> m_Shader;
    Carrot::Ref<Carrot::Texture2D> m_Texture2D;
    Carrot::Ref<Carrot::OrthographicCameraController> m_CameraController;
    Carrot::Ref<Carrot::Texture2D> test_Texture2D;
};