#pragma once

#include <sstream>
#include "Event.h"

namespace Carrot
{
    class CARROT_API MouseMovedEvent : public Event{
    public:
        MouseMovedEvent(float x,float y)
            : Event(),m_MouseX(x), m_MouseY(y){}

        inline float GetX() const {return m_MouseX;}
        inline float GetY() const {return m_MouseY;}

        std::string ToString() const override{
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryInput|EventCategoryMouse)
    private:
        float m_MouseX, m_MouseY; //鼠标在屏幕上xy的位置
    };

    class CARROT_API MouseScrolledEvent : public Event{
    public:
        MouseScrolledEvent(float x,float y)
            : m_XOffset(x), m_YOffset(y){}

        inline float GetX() const {return m_XOffset;}
        inline float GetY() const {return m_YOffset;}

        std::string ToString() const override{
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryInput|EventCategoryMouse)
    private:
        float m_XOffset, m_YOffset; //鼠标offset 通常 +1or-1
    };

    class CARROT_API MouseButtonEvent : public Event{
    public:

        inline int GetMouseButton() const {return m_Button;}

        EVENT_CLASS_CATEGORY(EventCategoryInput|EventCategoryMouse)
    protected:
        MouseButtonEvent(int button)
            : m_Button(button){}
        int m_Button; //鼠标的按键
    };

    class CARROT_API MouseButtonPressedEvent : public MouseButtonEvent{
    public:
        MouseButtonPressedEvent(int button)
            :MouseButtonEvent(button){}

        std::string ToString() const override{
            std::stringstream ss;
            ss<< "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class CARROT_API MouseButtonReleasedEvent : public MouseButtonEvent{
    public:
        MouseButtonReleasedEvent(int button)
            :MouseButtonEvent(button){}

        std::string ToString() const override{
            std::stringstream ss;
            ss<< "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseButtonReleased)
    };

} // namespace Carrot
