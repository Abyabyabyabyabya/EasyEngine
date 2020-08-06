///
/// \file   input_state.hpp
/// \brief  入力状態に関する定義群ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/5
///             - ヘッダ追加
///             - InputFlagType 定義
///             - 入力状態判定関数定義
///
#ifndef INCLUDED_EGEG_ILIB_INPUT_STATE_HEADER_
#define INCLUDED_EGEG_ILIB_INPUT_STATE_HEADER_

#include <cstdint>

namespace easy_engine {
namespace i_lib {

using InputFlagType = uint8_t;

constexpr InputFlagType kNoInput = 0b000U; ///< 入力なし
constexpr InputFlagType kInput   = 0b001U; ///< 入力ありフラグ
constexpr InputFlagType kDown    = 0b010U; ///< 押下直後フラグ
constexpr InputFlagType kUp      = 0b100U; ///< 離上直後フラグ

///
/// \brief  入力ありかどうか判定
///
/// \param[in] State : 判定する入力の状態
///
/// \return 入力があればtrue　なければfalse
///
inline constexpr bool isInput(const InputFlagType State) noexcept {
    return State & kInput;
}

///
/// \brief  入力が継続状態にあるかどうか判定
///
///         入力直後の状態はfalseとみなします。
///
/// \param[in] State : 判定する入力の状態
///
/// \return 継続状態であればtrue　でなければfalse
///
inline constexpr bool isHold(const InputFlagType State) noexcept {
    return State == kInput;
}

///
/// \brief  入力直後の状態かどうか判定
///
/// \param[in] State : 判定する入力の状態
///
/// \return 入力直後であればtrue　そうでなければfalse
///
inline constexpr bool isDown(const InputFlagType State) noexcept {
    return State & kDown;
}

///
/// \brief  入力解除直後の状態かどうか判定
///
/// \param[in] State : 判定する入力の状態
///
/// \ return 解除直後であればtrue　そうでなければfalse
///
inline constexpr bool isUp(const InputFlagType State) noexcept {
    return State & kUp;
}

} // namespace i_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_ILIB_INPUT_STATE_HEADER_
// EOF
