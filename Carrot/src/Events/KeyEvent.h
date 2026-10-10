#pragma once

#include "Event.h"
#include <sstream>

namespace Carrot
{
    class CARROT_API KeyEvent: public Event{
    public:
        inline int GetKeyCode() const {return m_KeyCode; }
        int GetScanCode() const { return m_ScanCode; }
        int GetModifiers() const { return m_Modifiers; }
        EVENT_CLASS_CATEGORY(EventCategoryKeyboard|EventCategoryInput) //这里是个宏,宏定义在Event头文件中,就不需要每次都写Event的方法了
    protected:
        KeyEvent(int keyCode, int scanCode = 0, int modifiers = 0)
            : m_KeyCode(keyCode), m_ScanCode(scanCode), m_Modifiers(modifiers){}

        int m_KeyCode;
        int m_ScanCode;
        int m_Modifiers;
    };

    class CARROT_API KeyPressedEvent : public KeyEvent{
    public:
        KeyPressedEvent(int keyCode, int repeatCount, int scanCode = 0, int modifiers = 0)
            : KeyEvent(keyCode, scanCode, modifiers), m_RepeatCount(repeatCount) {
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
        KeyReleasedEvent(int keyCode, int scanCode = 0, int modifiers = 0)
            : KeyEvent(keyCode, scanCode, modifiers){

            }

        std::string ToString() const override{
          std::stringstream ss;
          ss <<"KeyReleasedEvent: " << m_KeyCode;
          return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
    
    // 文本输入使用 Unicode 码点，不能用按键编号代替。
    class CARROT_API KeyTypedEvent : public Event {
    public:
        explicit KeyTypedEvent(unsigned int codepoint) : m_Codepoint(codepoint) {}
        unsigned int GetCodepoint() const { return m_Codepoint; }
        EVENT_CLASS_TYPE(KeyTyped)
        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    private:
        unsigned int m_Codepoint;
    };
} // namespace CARROT
