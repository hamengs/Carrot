 #pragma once

 #include "Core.h"
 #include "Events/Event.h"

 namespace Carrot
 {
    class CARROT_API Layer {
    public:
        Layer(const std::string& name = "Layer");
        //派生层需要调用各自的析构方法来正确释放内存
        virtual ~Layer();

        virtual void OnUpdate(){}
        virtual void OnEvent(Event& e){};
        virtual void OnAttach(){}
        virtual void OnDetach(){}

        //可有可无,不会对性能造成很大影响
        inline const std::string& GetName() const {return m_DebugName;}

    protected:
        std::string m_DebugName;
    };
 } // namespace Carrot
 