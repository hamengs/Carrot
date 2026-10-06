#pragma once

#include "Core.h"
#include "Layer.h"

namespace Carrot
{
    class CARROT_API LayerStack{
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverLayer(Layer* layer);

        void PopLayer(Layer* layer);
        void PopOverLayer(Layer* layer);

        std::vector<Layer*>::iterator begin(){return m_Layers.begin();}
        std::vector<Layer*>::iterator end(){return m_Layers.end();}
        
    private:
        //使用指针确保派生类各自调用派生方法,C++中多态使用指针,或者说引用& Ex. Base& b =  derive b.update
        //Java和C#自动存储的是引用
        std::vector<Layer*> m_Layers;
        //普通层和overlay层用一个index来做划分,他们都在同一个vector里
        unsigned int m_LayerInsertIndex = 0;
    };
} // namespace Carrot
