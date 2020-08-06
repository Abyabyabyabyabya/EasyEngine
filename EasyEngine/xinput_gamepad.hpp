///
/// \file   xinput_gamepad.hpp
/// \brief  入力デバイス「XInputゲームパッド」定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/5
///             - ヘッダ追加
///
#ifndef INCLUDED_EGEG_ILIB_XINPUT_GAMEPAD_HEADER_
#define INCLUDED_EGEG_ILIB_XINPUT_GAMEPAD_HEADER_

#include <Windows.h> // target platform
#include <Xinput.h>
#include "input_device.hpp"

namespace easy_engine {
namespace i_lib {

///
/// \class  XInputGamepad
/// \brief  XInput入力デバイス
/// 
class XInputGamepad : public InputDevice {
public :
    struct State {
        bool connected; ///< true:接続済み　false:接続なし

        InputFlagType dpad_up;
        InputFlagType dpad_down;
        InputFlagType dpad_left;
        InputFlagType dpad_right;
        InputFlagType lstick_up;
        InputFlagType lstick_down;
        InputFlagType lstick_left;
        InputFlagType lstick_right;
        InputFlagType rstick_up;
        InputFlagType rstick_down;
        InputFlagType rstick_left;
        InputFlagType rstick_right;
        InputFlagType start;
        InputFlagType back;
        InputFlagType lthumbstick;
        InputFlagType rthumbstick;
        InputFlagType lshoulder;
        InputFlagType rshoulder;
        InputFlagType a;
        InputFlagType b;
        InputFlagType x;
        InputFlagType y;

        float ltrigger;      ///< 範囲 - [0.0F : 1.0F]
        float rtrigger;      ///< 範囲 - [0.0F : 1.0F]
        float lthumbstick_x; ///< 範囲 - [0.0F : 1.0F]
        float lthumbstick_y; ///< 範囲 - [0.0F : 1.0F]
        float rthumbstick_x; ///< 範囲 - [0.0F : 1.0F]
        float rthumbstick_y; ///< 範囲 - [0.0F : 1.0F]
    };

    const State& getState() const noexcept { return state_; }

protected :
    void updateState(DWORD);
    State state_{};
    _XINPUT_STATE last_state_{};
};

  namespace xinput_impl_ns {
    template <DWORD UserIdx>
    class XInputGamepadImpl : public XInputGamepad {
    public :
        void update() override { updateState(UserIdx); }
    };
  } // namespace xinput_impl_ns
  
using XInputP1 = xinput_impl_ns::XInputGamepadImpl<0UL>; ///< ゲームパッド0
using XInputP2 = xinput_impl_ns::XInputGamepadImpl<1UL>; ///< ゲームパッド1
using XInputP3 = xinput_impl_ns::XInputGamepadImpl<2UL>; ///< ゲームパッド2
using XInputP4 = xinput_impl_ns::XInputGamepadImpl<3UL>; ///< ゲームパッド3

} // namespace i_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_ILIB_XINPUT_GAMEPAD_HEADER_
// EOF
