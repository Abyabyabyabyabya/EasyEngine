///
/// \file   xinput_controller.hpp
/// \brief  XInputGamePad�p�R���g���[���[��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/8/6
///             - �w�b�_�ǉ�
///             - XInputCtrlerImpl ��`
///             - XInputController ��`
///
#ifndef INCLUDED_EGEG_ILIB_XINPUT_CONTROLLER_HEADER_
#define INCLUDED_EGEG_ILIB_XINPUT_CONTROLLER_HEADER_

#include <array>
#include "controller.hpp"
#include "xinput_gamepad.hpp"
#include "utility_function.hpp"

namespace easy_engine {
namespace i_lib {
  namespace xcontroller_impl {
    class XInputCtrlerImpl {
    public :
        enum class Buttons {
            kDpadUp,
            kDpadDown,
            kDpadLeft,
            kDpadRight,
            kLStickUp,
            kLStickDown,
            kLStickLeft,
            kLStickRight,
            kRStickUp,
            kRStickDown,
            kRStickLeft,
            kRStickRight,
            kStart,
            kBack,
            kLThumbStick,
            kRThumbStick,
            kLShoulder,
            kRShoulder,
            kA,
            kB,
            kX,
            kY
        };
        enum class Triggers {
            kLTrigger,
            kRTrigger
        };
        enum class Sticks {
            kLStick,
            kRStick
        };

        XInputCtrlerImpl(const XInputGamepad* Gamepad) noexcept : gamepad_{Gamepad} {}

        void resetGamepad(const XInputGamepad* Gamepad=nullptr) noexcept { gamepad_ = Gamepad; }
        const XInputGamepad* getGamepad() const noexcept { return gamepad_; }

    private :
        const XInputGamepad* gamepad_;
    };
  } // namespace xcontroller_impl

///
/// \class  XInputController
/// \brief  XInputGamePad�p�R���g���[���[
///
///         �o�^����֐��́A���͂̏�Ԃ������Ŏ󂯎���K�v������܂��B
///         �o�^(map)����ہA�֐��ɑΉ�����L�[���w�肷�邱�ƂŁA�֐��ɑΉ�����L�[�̏�Ԃ��n�����悤�ɂȂ�܂��B
///         ���ɃL�[�̎�ނƓo�^�ł���֐��̌^�������܂��B
///         Buttons  : void (InputFlagType) �c �����ɂ͑Ή�����{�^���̓��͏�ԃt���O���n����܂��B
///         Triggers : void (float)         �c �����ɂ́A�Ή�����g���K�[�̓��͒l([0.0F : 1.0F])���n����܂��B
///         Sticks   : void (float, float)  �c �����ɂ́A�Ή�����X�e�B�b�N�̓��͒l(x, y���ꂼ��[0.0F : 1.0F])���n����܂��B
///
/// \tparam TargetTy : ����Ώۂ̃I�u�W�F�N�g�^
///
/// \attention const�����o�֐� �͓o�^�ł��܂���B
///
template <class TargetTy>
class XInputController : public Controller<TargetTy>, public xcontroller_impl::XInputCtrlerImpl {
public :
    XInputController(const XInputGamepad* Gamepad=nullptr, TargetTy* Target=nullptr) :
        Controller<TargetTy>{Target},
        XInputCtrlerImpl{Gamepad} {
        button_related_funcs_.fill(nullptr);
        trigger_related_funcs_.fill(nullptr);
        stick_related_funcs_.fill(nullptr);
    }

    ///
    /// \brief  �L�[�Ɗ֐��̃}�b�s���O
    ///
    ///         ��x�ɕ����̃y�A���}�b�s���O���邱�Ƃ��ł��܂��B
    ///         ���̏ꍇ�́A�u�L�[, �֐��|�C���^�v�̃y�A�𑱂��ē��͂��Ă��������B
    ///         ��)  �cmap(�ckDpadUp , &Hoge::jump,
    ///                    �ckA      , &Hoge::shot,
    ///                    �ckY      , &Hoge::pause);
    ///
    /// \tparam KeyTy     : �L�[�̌^(Buttons, Triggers, Sticks�̂����ꂩ)
    /// \tparam FArgTypes : �}�b�v����֐��̈����^���X�g
    /// \tparam RestTypes : �c��̃}�b�v�y�A�^���X�g
    /// \param[in] Key      : �֐����}�b�v����L�[
    /// \param[in] Function : �}�b�v����֐�
    /// \param[in] Rest     : ���̃y�A
    /// 
    template<class KeyTy, class ...FArgTypes, class ...RestTypes>
    void map(const KeyTy Key, void(TargetTy::*Function)(FArgTypes...), RestTypes ...Rest) noexcept {
        mapImpl(Key, Function);
        map(Rest...);
    }

    ///
    /// \brief  �L�[�Ɗ֐��̃}�b�v������
    ///
    ///         ��x�ɕ����̃}�b�v���������邱�Ƃ��ł��܂��B
    ///         ���̏ꍇ�́A�����������L�[�𑱂��ē��͂��Ă��������B
    ///         ��) �cunmap(�ckDpadUp, �ckA);   // ����ł��Ȃ��悤�}�b�v������
    ///
    /// \tparam KeyTy        : �L�[�̌^(Buttons, Triggers, Sticks�̂����ꂩ)
    /// \tparam RestKeyTypes : �c��̃L�[�̌^
    /// \param[in] Key   : �֐��Ƃ̃}�b�v����������L�[
    /// \param[in] Rests : �ǉ��ŉ�������L�[
    ///
    template <class KeyTy, class ...RestKeyTypes>
    void unmap(const KeyTy Key, const RestKeyTypes ...Rests) noexcept {
        unmapImpl(Key);
        unmap(Rests...);
    }

// override
    void run() override {
        if(!this->getTarget()) return;
        const auto& state = getGamepad()->getState();
        if(state.connected) {
            safeInvoke(Buttons::kDpadUp, state.dpad_up);
            safeInvoke(Buttons::kDpadDown, state.dpad_down);
            safeInvoke(Buttons::kDpadLeft, state.dpad_left);
            safeInvoke(Buttons::kDpadRight, state.dpad_right);
            safeInvoke(Buttons::kLStickUp, state.lstick_up);
            safeInvoke(Buttons::kLStickDown, state.lstick_down);
            safeInvoke(Buttons::kLStickLeft, state.lstick_left);
            safeInvoke(Buttons::kLStickRight, state.lstick_right);
            safeInvoke(Buttons::kRStickUp, state.rstick_up);
            safeInvoke(Buttons::kRStickDown, state.rstick_down);
            safeInvoke(Buttons::kRStickLeft, state.rstick_left);
            safeInvoke(Buttons::kRStickRight, state.rstick_right);
            safeInvoke(Buttons::kStart, state.start);
            safeInvoke(Buttons::kBack, state.back);
            safeInvoke(Buttons::kLThumbStick, state.lthumbstick);
            safeInvoke(Buttons::kRThumbStick, state.rthumbstick);
            safeInvoke(Buttons::kLShoulder, state.lshoulder);
            safeInvoke(Buttons::kRShoulder, state.rshoulder);
            safeInvoke(Buttons::kA, state.a);
            safeInvoke(Buttons::kB, state.b);
            safeInvoke(Buttons::kX, state.x);
            safeInvoke(Buttons::kY, state.y);
            safeInvoke(Triggers::kLTrigger, state.ltrigger);
            safeInvoke(Triggers::kRTrigger, state.rtrigger);
            safeInvoke(Sticks::kLStick, state.lthumbstick_x, state.lthumbstick_y);
            safeInvoke(Sticks::kRStick, state.rthumbstick_x, state.rthumbstick_y);
        }
    }

private :
    void map() const noexcept {}
    void unmap() const noexcept {}
    template <class Ty, class FTy>
    void mapImpl(const Ty, const FTy) const noexcept {
        static_assert(false, "such key or such function pointer is not supported");
    }
    void mapImpl(const Buttons Button, void(TargetTy::*Function)(InputFlagType)) noexcept {
        button_related_funcs_[t_lib::enumValue(Button)] = Function;
    }
    void mapImpl(const Triggers Trigger, void(TargetTy::*Function)(float)) noexcept {
        trigger_related_funcs_[t_lib::enumValue(Trigger)] = Function;
    }
    void mapImpl(const Sticks Stick, void(TargetTy::*Function)(float, float)) noexcept {
        stick_related_funcs_[t_lib::enumValue(Stick)] = Function;
    }
    template <class InvalidTy> void unmapImpl(const InvalidTy) const noexcept {
        static_assert(false, "such key is not supported");
    }
    void unmapImpl(const Buttons Button) noexcept {
        button_related_funcs_[t_lib::enumValue(Button)] = nullptr;
    }
    void unmapImpl(const Triggers Trigger) noexcept {
        trigger_related_funcs_[t_lib::enumValue(Trigger)] = nullptr;
    }
    void unmapImpl(const Sticks Stick) noexcept {
        stick_related_funcs_[t_lib::enumValue(Stick)] = nullptr;
    }
    void safeInvoke(const Buttons Button, const InputFlagType State) const noexcept {
        if(auto func = button_related_funcs_[t_lib::enumValue(Button)]) this->invoke(func, State);
    }
    void safeInvoke(const Triggers Trigger, const float State) const noexcept {
        if(auto func = trigger_related_funcs_[t_lib::enumValue(Trigger)]) this->invoke(func, State);
    }
    void safeInvoke(const Sticks Stick, const float X, const float Y) const noexcept {
        if(auto func = stick_related_funcs_[t_lib::enumValue(Stick)]) this->invoke(func, X, Y);
    }

    std::array<void(TargetTy::*)(InputFlagType), 22U> button_related_funcs_;
    std::array<void(TargetTy::*)(float), 2U>          trigger_related_funcs_;
    std::array<void(TargetTy::*)(float, float), 2U>   stick_related_funcs_;
};

} // namespace i_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_ILIB_XINPUT_CONTROLLER_HEADER_
// EOF
