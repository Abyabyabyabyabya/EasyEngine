// 作成者 : 板場
/******************************************************************************

    include

******************************************************************************/
#include "xinput_gamepad.hpp"

/******************************************************************************

    Library

******************************************************************************/
#pragma comment(lib, "xinput.lib")

/******************************************************************************

    definition & declaration

******************************************************************************/
namespace xinput_ns = easy_engine::i_lib;
namespace xinput_impl_ns = easy_engine::i_lib::xinput_impl_ns;
namespace {
    constexpr float normalizeTrigger(const BYTE Input) noexcept { return Input * (1.0F/255.0F); }
    constexpr float normalizeStick(const SHORT Input) noexcept { return Input * (1.0F/32767.0F); }
    constexpr bool  detectStickInput(const float Input) noexcept { return Input>0 ? Input>=0.8F : Input<=-0.8F; }
    constexpr xinput_ns::InputFlagType newState(const bool Last, const bool Curr) noexcept {
        if(!Last && !Curr) return xinput_ns::kNoInput;
        if(Last && Curr)   return xinput_ns::kInput;
        if(Curr)           return (xinput_ns::kInput | xinput_ns::kDown);
                           return xinput_ns::kUp;
    }
    constexpr xinput_ns::InputFlagType newButtonState(const WORD Last, const WORD Curr, const int Button) noexcept {
        return newState(Last&Button, Curr&Button);
    }
    constexpr float adjustStick(const SHORT Raw, const int DeadZone) noexcept { 
        if(Raw<DeadZone && Raw>-DeadZone) return 0.0F;
        const float result = normalizeStick(Raw);
        return result<-1.0F ? -1.0F : result; // 正規化の際、マイナス方向にオーバーする可能性がある
    }
    constexpr bool isStickUp(const float Y) noexcept    { return Y>0 ? detectStickInput(Y) : false; }
    constexpr bool isStickDown(const float Y) noexcept  { return Y<0 ? detectStickInput(Y) : false; }
    constexpr bool isStickLeft(const float X) noexcept  { return X<0 ? detectStickInput(X) : false; }
    constexpr bool isStickRight(const float X) noexcept { return X>0 ? detectStickInput(X) : false; }
} // unnamed namespace

/******************************************************************************

    XInputGamepad::

******************************************************************************/
void xinput_ns::XInputGamepad::updateState(const DWORD User) {
    _XINPUT_STATE curr_state{};

    if( XInputGetState(User, &curr_state)==ERROR_SUCCESS) {
        state_.connected = true;
        if(curr_state.dwPacketNumber!=last_state_.dwPacketNumber) {
          // ボタン
            // note : フラグをシフトさせて処理を単純にしようかと考えたが、フラグの値が飛んでいる箇所があるので断念
            const WORD last_buttons = last_state_.Gamepad.wButtons;
            const WORD curr_buttons = curr_state.Gamepad.wButtons;
            state_.dpad_up = newButtonState(last_buttons, curr_buttons, XINPUT_GAMEPAD_DPAD_UP);
            state_.dpad_down = newButtonState(last_buttons, curr_buttons, XINPUT_GAMEPAD_DPAD_DOWN);
            state_.dpad_left = newButtonState(last_buttons, curr_buttons, XINPUT_GAMEPAD_DPAD_LEFT);
            state_.dpad_right = newButtonState(last_buttons, curr_buttons, XINPUT_GAMEPAD_DPAD_RIGHT);
            state_.start = newButtonState(last_buttons, curr_buttons, XINPUT_GAMEPAD_START);
            state_.back = newButtonState(last_buttons, curr_buttons, XINPUT_GAMEPAD_BACK);
            state_.lthumbstick = newButtonState(last_buttons, curr_buttons, XINPUT_GAMEPAD_LEFT_THUMB);
            state_.rthumbstick = newButtonState(last_buttons, curr_buttons, XINPUT_GAMEPAD_RIGHT_THUMB);
            state_.lshoulder = newButtonState(last_buttons, curr_buttons, XINPUT_GAMEPAD_LEFT_SHOULDER);
            state_.rshoulder = newButtonState(last_buttons, curr_buttons, XINPUT_GAMEPAD_RIGHT_SHOULDER);
            state_.a = newButtonState(last_buttons, curr_buttons, XINPUT_GAMEPAD_A);
            state_.b = newButtonState(last_buttons, curr_buttons, XINPUT_GAMEPAD_B);
            state_.x = newButtonState(last_buttons, curr_buttons, XINPUT_GAMEPAD_X);
            state_.y = newButtonState(last_buttons, curr_buttons, XINPUT_GAMEPAD_Y);
          // トリガー
            state_.ltrigger = normalizeTrigger(curr_state.Gamepad.bLeftTrigger);
            state_.rtrigger = normalizeTrigger(curr_state.Gamepad.bRightTrigger);
          // スティック
            const float last_lx = state_.lthumbstick_x; // [0.0F : 1.0F]
            const float last_ly = state_.lthumbstick_y; // [0.0F : 1.0F]
            const float last_rx = state_.rthumbstick_x; // [0.0F : 1.0F]
            const float last_ry = state_.rthumbstick_y; // [0.0F : 1.0F]
            state_.lthumbstick_x = adjustStick(curr_state.Gamepad.sThumbLX, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
            state_.lthumbstick_y = adjustStick(curr_state.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
            state_.rthumbstick_x = adjustStick(curr_state.Gamepad.sThumbRX, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
            state_.rthumbstick_y = adjustStick(curr_state.Gamepad.sThumbRY, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
            state_.lstick_up = newState(isStickUp(last_ly), isStickUp(state_.lthumbstick_y));
            state_.lstick_down = newState(isStickDown(last_ly), isStickDown(state_.lthumbstick_y));
            state_.lstick_left = newState(isStickLeft(last_lx), isStickLeft(state_.lthumbstick_x));
            state_.lstick_right = newState(isStickRight(last_lx), isStickRight(state_.lthumbstick_x));
            state_.rstick_up = newState(isStickUp(last_ry), isStickUp(state_.rthumbstick_y));
            state_.rstick_down = newState(isStickDown(last_ry), isStickDown(state_.rthumbstick_y));
            state_.rstick_left = newState(isStickLeft(last_rx), isStickLeft(state_.rthumbstick_x));
            state_.rstick_right = newState(isStickRight(last_rx), isStickRight(state_.rthumbstick_x));
           
            // 次更新時用に状態を保存
            last_state_ = curr_state;
        }
        else {
          // コントローラーの変更なし(Down, Upフラグ下げるだけ)
            for(int i=&state_.y-&state_.dpad_up; i>=0; --i)
                *(&state_.dpad_up+i) &= ~(kDown|kUp);
        }
    }
    else 
        // デバイスが接続されていない
        state_.connected = false;
}
// EOF
