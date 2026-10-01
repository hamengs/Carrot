#pragma once

#include "Event.h"
#include <sstream>

namespace Carrot
{
    class CARROT_API KeyEvent: public Event{
    public:
        inline int GetKeyCode() const {return m_KeyCode; }
        EVENT_CLASS_CATEGORY(EventCategoryKeyboard|EventCategoryInput) //这里是个宏,宏定义在Event头文件中,就不需要每次都写Event的方法了
    protected:
        KeyEvent(int keyCode)
            : m_KeyCode(keyCode){} //对于一个KeyEvent,共有的资源是keycode

        int m_KeyCode;
    };

    class CARROT_API KeyPressedEvent : public KeyEvent{
    public:
        KeyPressedEvent(int keyCode, int repeatCount)
            : KeyEvent(keyCode), m_RepeatCount(repeatCount) {
            }   // 如果基类没有无参构造,子类必须显示调用父类构造函数来构建父类
                // 在这个例子中就是KeyEvent(keycode)

        inline int GetRepeatCount() const {return m_RepeatCount; }

        std::string ToString() const override{
          std::stringstream ss;
          ss <<"KeyPressedEvent: " << m_KeyCode << "(" << m_RepeatCount << "repeats)";
          return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    private:
        int m_RepeatCount; //这个是用来计数Key按下后持续按下了多少次
    };

    class CARROT_API KeyReleasedEvent: public KeyEvent{
    public:
        KeyReleasedEvent(int keyCode)
            : KeyEvent(keyCode){

            }

        std::string ToString() const override{
          std::stringstream ss;
          ss <<"KeyReleasedEvent: " << m_KeyCode;
          return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
} // namespace CARROT
