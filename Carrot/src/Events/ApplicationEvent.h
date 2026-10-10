#pragma once

#include "Event.h"
#include <sstream>

namespace Carrot
{
    class CARROT_API WindowFocusEvent : public Event {
    public:
        EVENT_CLASS_TYPE(WindowFocus)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class CARROT_API WindowLostFocusEvent : public Event {
    public:
        EVENT_CLASS_TYPE(WindowLostFocus)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class CARROT_API WindowResizeEvent : public Event{
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            :m_Width(width), m_Height(height){}

        inline unsigned int GetWidth() const {return m_Width;}
        inline unsigned int GetHeight() const {return m_Height;}

        std::string ToString() const override{
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        EVENT_CLASS_CATEGORY(EventCategoryApplication)
        EVENT_CLASS_TYPE(WindowResize)
    private:
        unsigned int m_Width, m_Height;
    };

    class CARROT_API WindowCloseEvent : public Event{
    public:
        WindowCloseEvent(){}

        EVENT_CLASS_CATEGORY(EventCategoryApplication)
        EVENT_CLASS_TYPE(WindowClose)
    };

    class CARROT_API AppTickEvent : public Event{
    public:
        AppTickEvent(){}

        EVENT_CLASS_CATEGORY(EventCategoryApplication)
        EVENT_CLASS_TYPE(AppTick)
    };

    class CARROT_API AppUpdateEvent : public Event{
    public:
        AppUpdateEvent(){}

        EVENT_CLASS_CATEGORY(EventCategoryApplication)
        EVENT_CLASS_TYPE(AppUpdate)
    };

    class CARROT_API AppRenderEvent : public Event{
    public:
        AppRenderEvent(){}

        EVENT_CLASS_CATEGORY(EventCategoryApplication)
        EVENT_CLASS_TYPE(AppRender)
    };
} // namespace Carrot
