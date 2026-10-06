#pragma once

#include "Core.h"
#include <string>
#include <functional>

namespace Carrot
{
    enum class EventType{
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    //用BIT位去分类,0001 0010这种,两个都是可以用|比如0010|0001 = 0011,判断时用&
    enum EventCategory {
        None                     = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput       = BIT(1),
        EventCategoryKeyboard    = BIT(2),
        EventCategoryMouse       = BIT(3),

    };

#define EVENT_CLASS_TYPE(type)  static EventType GetStaticType() {return EventType::type;}\
                                virtual EventType GetEventType() const override {return GetStaticType();}\
                                virtual const char* GetName() const override {return #type;}


#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}

    class CARROT_API Event
    {
        friend class EventDispatcher;
    protected:
        virtual ~Event() = default;
        bool m_Handled = false;
    public:
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const {return GetName(); }
        inline virtual bool Handled() const {return m_Handled;}

        inline bool IsInCategory(EventCategory category) const{
            return GetCategoryFlags() & category; //通过与比较来判断位是否是对应事件类
        }
    };

    class EventDispatcher{
        template<typename T>
        using EventFn = std::function<bool(T&)>; //std::function的别名,保存一个"返回bool接受一个泛型T的引用"的函数
      public:
        EventDispatcher(Event &event) : m_Event(event) {}

        template <typename T>
        bool Dispatch(EventFn<T> func) { //需要一个func,func返回bool接受一个T,
            if (m_Event.GetEventType() ==
                T::GetStaticType()) { // 首先判定dispatcher的事件类型是否和调用的方法所属的类型一致
                m_Event.m_Handled =
                    func(static_cast<T&>(m_Event));  // 一致则把对应事件传进去,由于参数是Event类,还需要静态转换成对应的事件类型
                    return true; // 同时返回true
            }
            return false; // 不一致则直接返回false
        }

      private:
        Event &m_Event; // 成员事件
    };

} // namespace Carrot
