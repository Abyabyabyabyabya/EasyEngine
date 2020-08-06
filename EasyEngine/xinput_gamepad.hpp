///
/// \file   xinput_gamepad.hpp
/// \brief  ���̓f�o�C�X�uXInput�Q�[���p�b�h�v��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/8/5
///             - �w�b�_�ǉ�
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
/// \brief  XInput���̓f�o�C�X
/// 
class XInputGamepad : public InputDevice {
public :
    struct State {
        bool connected; ///< true:�ڑ��ς݁@false:�ڑ��Ȃ�

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

        float ltrigger;      ///< �͈� - [0.0F : 1.0F]
        float rtrigger;      ///< �͈� - [0.0F : 1.0F]
        float lthumbstick_x; ///< �͈� - [0.0F : 1.0F]
        float lthumbstick_y; ///< �͈� - [0.0F : 1.0F]
        float rthumbstick_x; ///< �͈� - [0.0F : 1.0F]
        float rthumbstick_y; ///< �͈� - [0.0F : 1.0F]
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
  
using XInputP1 = xinput_impl_ns::XInputGamepadImpl<0UL>; ///< �Q�[���p�b�h0
using XInputP2 = xinput_impl_ns::XInputGamepadImpl<1UL>; ///< �Q�[���p�b�h1
using XInputP3 = xinput_impl_ns::XInputGamepadImpl<2UL>; ///< �Q�[���p�b�h2
using XInputP4 = xinput_impl_ns::XInputGamepadImpl<3UL>; ///< �Q�[���p�b�h3

} // namespace i_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_ILIB_XINPUT_GAMEPAD_HEADER_
// EOF
