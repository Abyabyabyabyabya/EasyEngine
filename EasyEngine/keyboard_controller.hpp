///
/// \file   keyboard_controller.hpp
/// \brief  キーボード用コントローラー
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/7
///             - ヘッダ追加
///             - Keys 定義
///             - KeyboardCtrlerImpl 定義
///             - KeyboardController 定義
///
#ifndef INCLUDED_EGEG_ILIB_KEYBOARD_CONTROLLER_HEADER_
#define INCLUDED_EGEG_ILIB_KEYBOARD_CONTROLLER_HEADER_

#include <cstdint>
#include <type_traits>
#include <array>
#include "controller.hpp"
#include "keyboard.hpp"

namespace easy_engine {
namespace i_lib {
  namespace keyboard_ctrler_impl {
    enum class Keys : uint8_t {
        kBackspace = 0x08,
        kTab,
        kEnter = 0x0D,
        kEscape = 0x1B,
        kSpace = 0x20,
        kLeft = 0x25,
        kUp,
        kRight,
        kDown,
        k0 = 0x30,
        k1,
        k2,
        k3,
        k4,
        k5,
        k6,
        k7,
        k8,
        k9,
        kA = 0x41,
        kB,
        kC,
        kD,
        kE,
        kF,
        kG,
        kH,
        kI,
        kJ,
        kK,
        kL,
        kM,
        kN,
        kO,
        kP,
        kQ,
        kR,
        kS,
        kT,
        kU,
        kV,
        kW,
        kX,
        kY,
        kZ,
        kNum0 = 0x60,
        kNum1,
        kNum2,
        kNum3,
        kNum4,
        kNum5,
        kNum6,
        kNum7,
        kNum8,
        kNum9,
        kF1 = 0x70,
        kF2,
        kF3,
        kF4,
        kF5,
        kF6,
        kF7,
        kF8,
        kF9,
        kF10,
        kF11,
        kF12,
        kLShift = 0xA0,
        kRShift,
        kLCtrl,
        kRCtrl,
        kLAlt,
        kRAlt,
        kColon = 0xBA,
        kSemiColon,
        kMinus,
        kPeriod,
        kSlash,
        kAtmark,
        kLSquareBracket = 0xDB,
        kBackSlash,
        kRSquareBracket,
        kCaret,
        kCapsLock = 0xF0
    };

    class KeyboardCtrlerImpl { // 非テンプレート部抽出
    public :
        KeyboardCtrlerImpl(const Keyboard* Device) noexcept : keyboard_{Device} {}
        void resetKeyboard(const Keyboard* Device=nullptr) noexcept { keyboard_ = Device; }
        const Keyboard* getKeyboard() const noexcept { return keyboard_; }

    private :
        const Keyboard* keyboard_;
    };
  } // namespace keyboard_ctrler_impl

template <class TargetTy>
class KeyboardController : public Controller<TargetTy>, private keyboard_ctrler_impl::KeyboardCtrlerImpl {
public :
    using Keys = keyboard_ctrler_impl::Keys;
    using KeyboardCtrlerImpl::resetKeyboard;
    using KeyboardCtrlerImpl::getKeyboard;

    ///
    /// \brief  コンストラクタ
    ///
    /// \param[in] Device : 入力を見るキーボード
    /// \param[in] Target : 操作対象
    ///
    KeyboardController(const Keyboard* Device=nullptr, TargetTy* Target=nullptr) :
        Controller<TargetTy>{Target},
        KeyboardCtrlerImpl{Device} {
        key_related_funcs_.fill(nullptr);
    }

    ///
    /// \brief  キーと関数のマッピング
    ///
    ///         一度に複数のペアをマッピングすることができます。
    ///         その場合は、「キー, 関数ポインタ」のペアを続けて入力してください。
    ///         例)  …map(…kUp   , &Hoge::jump,
    ///                    …kSpace, &Hoge::shot, … );
    ///
    /// \tparam KeyTy     : キーの型
    /// \tparam FTy       : マップする関数ポインタの型
    /// \tparam RestTypes : 残りのマップペアリスト
    /// \param[in] Key      : 関数をマップするキー
    /// \param[in] Function : マップする関数
    /// \param[in] Rests    : 他のペア
    ///
    template <class KeyTy, class FTy, class ...RestTypes>
    void map(const KeyTy Key, const FTy Function, RestTypes ...Rests) noexcept {
        mapImpl(Key, Function);
        map(Rests...);
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
        const auto& state = getKeyboard()->getState();
        for(auto i=t_lib::enumValue(Keys::kBackspace); i<key_related_funcs_.size(); ++i) {
            if(auto func = key_related_funcs_[i])
                this->invoke(func, *(state.padding0+i));
        }
    }
private :
    void map() const noexcept {}
    template <class InvalidKTy, class InvalidFTy, class=std::enable_if_t<!std::is_same_v<InvalidKTy, Keys> ||
      !std::is_convertible_v<InvalidFTy, void(TargetTy::*)(InputFlagType)>>> // 例外指定の違いは許可
    void mapImpl(const InvalidKTy, const InvalidFTy) const noexcept {
        static_assert(false, "such key or such function is not supported");
    }
    void mapImpl(const Keys Key, void(TargetTy::*Function)(InputFlagType)) noexcept {
        key_related_funcs_[t_lib::enumValue(Key)] = Function;
    }
    void unmap() const noexcept {}
    template <class InvalidKTy>
    void unmapImpl(const InvalidKTy) noexcept {
        static_assert(false, "such key is not supported");
    }
    void unmapImpl(const Keys Key) noexcept {
        key_related_funcs_[t_lib::enumValue(Key)] = nullptr;
    }
    
    std::array<void(TargetTy::*)(InputFlagType), 241/*=Keys::kCapsLock+1*/> key_related_funcs_;
};

} // namespace i_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_ILIB_KEYBOARD_CONTROLLER_HEADER_
// EOF
