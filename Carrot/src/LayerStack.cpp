#include "LayerStack.h"

namespace Carrot
{
    LayerStack::LayerStack(){}
    LayerStack::~LayerStack(){
        for(auto layer : m_Layers){
            layer->OnDetach();
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer){
        //emplace,在指定位置插入
        m_Layers.emplace(m_Layers.begin()+m_LayerInsertIndex,layer);
        //更新计数器
        m_LayerInsertIndex++;
    }

    void LayerStack::PushOverLayer(Layer* layer){
        m_Layers.push_back(layer);
    }

    void LayerStack::PopLayer(Layer* layer){
        //先确定查找范围,确保不去寻找overlayer,不然可能错误减少index
        auto boundary = m_Layers.begin() + m_LayerInsertIndex;
        auto l = std::find(m_Layers.begin(),boundary,layer);
        if(l!=m_Layers.end()){
            m_Layers.erase(l);
            m_LayerInsertIndex--;
        }

    }

    void LayerStack::PopOverLayer(Layer* layer){
        //确定寻找范围
        auto boundary = m_Layers.begin() + m_LayerInsertIndex;
        auto l = std::find(boundary,m_Layers.end(),layer);
        if(l!=m_Layers.end()){
            m_Layers.erase(l);
        }
    }
} // namespace Carrot
