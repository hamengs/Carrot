 #pragma once

 #include "Core.h"
 #include "Events/Event.h"
 #include <string>

 namespace Carrot
 {
    class CARROT_API Layer {
    public:
        Layer(const std::string& name = "Layer");
        //派生层需要调用各自的析构方法来正确释放内存
        virtual ~Layer();

        virtual void OnUpdate(){}
        virtual void OnEvent(Event&){}
        virtual void OnAttach(){}
        virtual void OnDetach(){}
        //每个层有自己的imguilayer,意味着每个层有自己的界面设计维护而不用放到Imguilayer层统一管理
        virtual void OnImGuiRender(){}

        //可有可无,不会对性能造成很大影响
        inline const std::string& GetName() const {return m_LayerName;}

    protected:
        std::string m_LayerName;
    };
 } // namespace Carrot
 