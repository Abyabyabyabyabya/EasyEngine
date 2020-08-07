///
/// \file   xinput_controller.hpp
/// \brief  XInputGamePad用コントローラー定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/6
///             - ヘッダ追加
///             - XInputCtrlerImpl 定義
///             - XInputController 定義
///
#ifndef INCLUDED_EGEG_ILIB_XINPUT_CONTROLLER_HEADER_
#define INCLUDED_EGEG_ILIB_XINPUT_CONTROLLER_HEADER_

#include <cstdint>
#include <array>
#include "controller.hpp"
#include "xinput_gamepad.hpp"
#include "utility_function.hpp"

namespace easy_engine {
namespace i_lib {
  namespace xcontroller_impl {
    enum class Buttons : std::uint8_t {
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
    enum class Triggers : std::uint8_t {
        kLTrigger,
        kRTrigger
    };
    enum class Sticks : std::uint8_t {
        kLStick,
        kRStick
    };

    class XInputCtrlerImpl { // 非テンプレート部抽出
    public :
        XInputCtrlerImpl(const XInputGamepad* Gamepad) noexcept : gamepad_{Gamepad} {}

        void resetGamepad(const XInputGamepad* Gamepad=nullptr) noexcept { gamepad_ = Gamepad; }
        const XInputGamepad* getGamepad() const noexcept { return gamepad_; }

    private :
        const XInputGamepad* gamepad_;
    };
  } // namespace xcontroller_impl

///
/// \class  XInputController
/// \brief  XInputGamePad用コントローラー
///
///         登録する関数は、入力の状態を引数で受け取れる必要があります。
///         登録(map)する際、関数に対応するキーを指定することで、関数に対応するキーの状態が渡されるようになります。
///         ↓にキーの種類と登録できる関数の型を示します。
///         Buttons  : void (InputFlagType) … 引数には対応するボタンの入力状態フラグが渡されます。
///         Triggers : void (float)         … 引数には、対応するトリガーの入力値([0.0F : 1.0F])が渡されます。
///         Sticks   : void (float, float)  … 引数には、対応するスティックの入力値(x, yそれぞれ[0.0F : 1.0F])が渡されます。
///
/// \tparam TargetTy : 操作対象のオブジェクト型
///
/// \attention constメンバ関数 は登録できません。
///
template <class TargetTy>
class XInputController : public Controller<TargetTy>, public xcontroller_impl::XInputCtrlerImpl {
public :
    using Buttons = xcontroller_impl::Buttons;
    using Triggers = xcontroller_impl::Triggers;
    using Sticks = xcontroller_impl::Sticks;
    using XInputCtrlerImpl::resetGamepad;
    using XInputCtrlerImpl::getGamepad;

    ///
    /// \brief  コンストラクタ
    ///
    /// \param[in] Gamepad : 入力を見るゲームパッド
    /// \param[in] Target  : 操作対象
    ///
    XInputController(const XInputGamepad* Gamepad=nullptr, TargetTy* Target=nullptr) :
        Controller<TargetTy>{Target},
        XInputCtrlerImpl{Gamepad} {
        button_related_funcs_.fill(nullptr);
        trigger_related_funcs_.fill(nullptr);
        stick_related_funcs_.fill(nullptr);
    }

    ///
    /// \brief  キーと関数のマッピング
    ///
    ///         一度に複数のペアをマッピングすることができます。
    ///         その場合は、「キー, 関数ポインタ」のペアを続けて入力してください。
    ///         例)  …map(…kDpadUp , &Hoge::jump,
    ///                    …kA      , &Hoge::shot,
    ///                    …kY      , &Hoge::pause);
    ///
    /// \tparam KeyTy     : キーの型(Buttons, Triggers, Sticksのいずれか)
    /// \tparam FArgTypes : マップする関数の引数型リスト
    /// \tparam RestTypes : 残りのマップペア型リスト
    /// \param[in] Key      : 関数をマップするキー
    /// \param[in] Function : マップする関数
    /// \param[in] Rest     : 他のペア
    /// 
    template<class KeyTy, class ...FArgTypes, class ...RestTypes>
    void map(const KeyTy Key, void(TargetTy::*Function)(FArgTypes...), RestTypes ...Rest) noexcept {
        mapImpl(Key, Function);
        map(Rest...);
    }

    ///
    /// \brief  キーと関数のマップを解除
    ///
    ///         一度に複数のマップを解除することができます。
    ///         その場合は、解除したいキーを続けて入力してください。
    ///         例) …unmap(…kDpadUp, …kA);   // 操作できないようマップを解除
    ///
    /// \tparam KeyTy        : キーの型(Buttons, Triggers, Sticksのいずれか)
    /// \tparam RestKeyTypes : 残りのキーの型
    /// \param[in] Key   : 関数とのマップを解除するキー
    /// \param[in] Rests : 追加で解除するキー
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
    template <class InvalidTy, class InvalidFTy>
    void mapImpl(const InvalidTy, const InvalidFTy) const noexcept {
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

    std::array<void(TargetTy::*)(InputFlagType), 22U/*=Buttons::kY+1*/>   button_related_funcs_;
    std::array<void(TargetTy::*)(float), 2U/*=Triggers::kRTrigger+1*/>    trigger_related_funcs_;
    std::array<void(TargetTy::*)(float, float), 2U/*=Sticks::kRStick+1*/> stick_related_funcs_;
};

} // namespace i_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_ILIB_XINPUT_CONTROLLER_HEADER_
// EOF
