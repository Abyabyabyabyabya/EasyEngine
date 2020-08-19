///
/// \file   input_device.hpp
/// \brief  入力デバイス基底定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/5
///             - ヘッダ追加
///             - InputDevice 定義
///
#ifndef INCLUDED_EGEG_ILIB_INPUT_DEVICE_HEADER_
#define INCLUDED_EGEG_ILIB_INPUT_DEVICE_HEADER_

#include "noncopyable.hpp"
#include "input_state.hpp"

namespace easy_engine {
namespace i_lib {

/******************************************************************************

    InputDevice

******************************************************************************/
///
/// \class  InputDevice
/// \brief  入力デバイス基底
///
///         入力に関するクラスはこのクラスを基底としてください。
///         コピーはデフォルトで禁止しています。
///         派生クラスで、コピーをサポートする場合は、明示的にコピー演算を定義してください。
///         
class InputDevice : t_lib::Noncopyable<InputDevice> {
public :
    virtual ~InputDevice() = default;

    ///
    /// \brief  更新処理
    ///
    ///         派生クラスはこの関数をオーバーライドし、
    ///         入力状態の更新を行ってください。
    ///
    virtual void update() = 0;
};

} // namespace i_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_ILIB_INPUT_DEVICE_HEADER_
// EOF
