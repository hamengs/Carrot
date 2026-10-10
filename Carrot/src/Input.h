#pragma once

#include "Core.h"
#include "Window.h"
#include <utility>
#include <array>
namespace Carrot
{
    class CARROT_API Input{
    public:
        virtual ~Input() = default;

        static void Init(Window& window);
        static void ShutDown();

        static void BeginFrame();
        static void OnEvent(Event& e);

        
        // 键盘状态由引擎事件更新，三个查询读取同一张状态表。
        static bool IsKeyDown(int keyCode);
        static bool WasKeyPressed(int keyCode);
        static bool WasKeyReleased(int keyCode);
        static bool IsKeyRepeat(int keyCode); // 本帧收到过系统按键重复事件。
        static bool IsKeyReleased(int keyCode){return WasKeyReleased(keyCode);}

        // 查询当前是否按住，不是“本帧刚按下”。
        static bool IsMouseButtonDown(int button);
        static bool WasMouseButtonPressed(int button);
        static bool WasMouseButtonReleased(int button);
        // 保留原来的接口名称，语义与 IsMouseButtonDown 一致。
        static bool IsMouseButtonPressed(int button){return IsMouseButtonDown(button);}
        // 相对于窗口内容区域左上角的位置，X 向右、Y 向下；不是 framebuffer 像素坐标。
        static std::pair<float, float> GetMousePosition(){return RequireInstance().GetMousePositionImple();}
        static float GetMouseX(){return GetMousePosition().first;}
        static float GetMouseY(){return GetMousePosition().second;}
        // 本帧收到过松开事件；查询不会消费标志，下一帧清零。
        static bool IsMouseButtonReleased(int button);
        // 本帧收到过非零滚动，即使正反方向累计抵消也返回 true。
        static bool IsMouseScrolled();
        static std::pair<float, float> GetScrollDelta();

    protected:

        virtual std::pair<float, float> GetMousePositionImple() = 0;

    private:
        static Input* s_Instance;
        static Input& RequireInstance();

        struct KeyState{
            bool Down = false;
            bool Pressed = false;
            bool Released = false;
            bool Repeat = false;
        };
        static constexpr int KeyCapacity = 512;

        std::array<KeyState,KeyCapacity> m_Keys{};
        static constexpr int MouseButtonCapacity = 8; // 当前 GLFW 按钮编号为 0..7。
        std::array<bool, MouseButtonCapacity> m_MouseReleased{};
        std::array<KeyState, MouseButtonCapacity> m_MouseButtons{};
        std::pair<float, float> m_ScrollDelta{0.0f, 0.0f};
        bool m_Scrolled = false;
        static bool IsValidKey(int key){
            return key >=0 && key < KeyCapacity;
        }
    };
} // namespace Carrot


