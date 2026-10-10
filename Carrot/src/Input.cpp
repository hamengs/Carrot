#include "Input.h"
#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include <stdexcept>

namespace Carrot
{
    Input& Input::RequireInstance(){
        if (!s_Instance)
            throw std::logic_error("Input is not initialized. Call Input::Init before using it.");
        return *s_Instance;
    }

    bool Input::IsKeyRepeat(int keyCode){
        auto& input = RequireInstance();
        return IsValidKey(keyCode) && input.m_Keys[keyCode].Repeat;
    }

    bool Input::IsMouseButtonDown(int button){
        auto& input = RequireInstance();
        return button >= 0 && button < MouseButtonCapacity && input.m_MouseButtons[button].Down;
    }

    bool Input::WasMouseButtonPressed(int button){
        auto& input = RequireInstance();
        return button >= 0 && button < MouseButtonCapacity && input.m_MouseButtons[button].Pressed;
    }

    bool Input::WasMouseButtonReleased(int button){
        return IsMouseButtonReleased(button);
    }

    bool Input::IsKeyDown(int keyCode){
        RequireInstance();
        return IsValidKey(keyCode) && s_Instance->m_Keys[keyCode].Down;
    }

    void Input::BeginFrame(){
        RequireInstance();
        for (auto& state : s_Instance->m_MouseButtons)
            state.Pressed = false;
        s_Instance->m_MouseReleased.fill(false);
        s_Instance->m_ScrollDelta = {0.0f, 0.0f};
        s_Instance->m_Scrolled = false;
        for(auto& state : s_Instance->m_Keys){
            state.Pressed = false;
            state.Released = false;
            state.Repeat = false;
        }
    }

    bool Input::WasKeyPressed(int keyCode){
        RequireInstance();
        return IsValidKey(keyCode)&&s_Instance->m_Keys[keyCode].Pressed;
    }

    bool Input::WasKeyReleased(int keyCode){
        RequireInstance();
        return IsValidKey(keyCode)&&s_Instance->m_Keys[keyCode].Released;
    }

    bool Input::IsMouseButtonReleased(int button){
        RequireInstance();
        return button >= 0 && button < MouseButtonCapacity &&
               s_Instance->m_MouseReleased[button];
    }

    bool Input::IsMouseScrolled(){
        RequireInstance();
        return s_Instance->m_Scrolled;
    }

    std::pair<float, float> Input::GetScrollDelta(){
        RequireInstance();
        return s_Instance->m_ScrollDelta;
    }

    void Input::OnEvent(Event& e){
        RequireInstance();
        EventDispatcher dispatcher(e);

        dispatcher.Dispatch<KeyPressedEvent>([](KeyPressedEvent& e){
            int key = e.GetKeyCode();
            if(!IsValidKey(key)){
                return false;
            }

            auto& state = s_Instance->m_Keys[key];
            if(e.GetRepeatCount()==0&&!state.Down){
                state.Pressed = true;
            }

            state.Down = true;
            if (e.GetRepeatCount() > 0)
                state.Repeat = true;
            return false;
        });

        dispatcher.Dispatch<KeyReleasedEvent>([](KeyReleasedEvent& e) {
            int key = e.GetKeyCode();
            if (!IsValidKey(key))
                return false;

            auto& state = s_Instance->m_Keys[key];

            if (state.Down)
                state.Released = true;

            state.Down = false;
            return false;
        });

        dispatcher.Dispatch<MouseButtonPressedEvent>([](MouseButtonPressedEvent& event) {
            const int button = event.GetMouseButton();
            if (button >= 0 && button < MouseButtonCapacity) {
                auto& state = s_Instance->m_MouseButtons[button];
                if (!state.Down)
                    state.Pressed = true;
                state.Down = true;
            }
            return false;
        });

        dispatcher.Dispatch<MouseButtonReleasedEvent>([](MouseButtonReleasedEvent& event) {
            const int button = event.GetMouseButton();
            if (button >= 0 && button < MouseButtonCapacity) {
                s_Instance->m_MouseReleased[button] = true;
                s_Instance->m_MouseButtons[button].Down = false;
            }
            return false;
        });

        dispatcher.Dispatch<MouseScrolledEvent>([](MouseScrolledEvent& event) {
            s_Instance->m_ScrollDelta.first += event.GetX();
            s_Instance->m_ScrollDelta.second += event.GetY();
            if (event.GetX() != 0.0f || event.GetY() != 0.0f)
                s_Instance->m_Scrolled = true;
            return false;
        });

        dispatcher.Dispatch<WindowLostFocusEvent>([](WindowLostFocusEvent&) {
            // 失焦时清除状态，避免按键卡住；这里不模拟一次游戏松开操作。
            for (auto& state : s_Instance->m_Keys)
                state = {};
            for (auto& state : s_Instance->m_MouseButtons)
                state = {};
            s_Instance->m_MouseReleased.fill(false);
            s_Instance->m_ScrollDelta = {0.0f, 0.0f};
            s_Instance->m_Scrolled = false;

            return false;
        });
    }
}

