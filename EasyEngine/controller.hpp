///
/// \file   controller.hpp
/// \brief  コントローラー定義ヘッダ
///
///         コントローラーは操作可能オブジェクトと入力デバイスの依存関係を吸収する目的で設計されます。
///         概念的に、コントローラーは入力キーと処理のマッピングを行います。
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/6
///             - ヘッダ追加
///             - Controller 定義
///
#ifndef INCLUDED_EGEG_ILIB_CONTROLLER_HEADER_
#define INCLUDED_EGEG_ILIB_CONTROLLER_HEADER_

#include <stdexcept>
#include "noncopyable.hpp"

namespace easy_engine {
namespace i_lib {
  namespace ctrler_impl {
      [[noreturn]] void invokeError() {
          throw std::logic_error{"invalid target function invoked"}; 
      }
  } // namespace ctrler_impl

///
/// \class  Controller
/// \brief  コントローラー基底
///
///         各種デバイスに対応した派生クラスで、入力に対応した関数を登録する処理を実装してください。
///         コントローラーはデバイスではありません。
///         意図しないコピーによる不具合を避けるため、デフォルトでコピーを禁止しています。
///         派生クラスで、コピーをサポートする場合は、明示的にコピー演算を定義してください。
///
/// \tparam TargetTy : 操作対象のオブジェクト型
///
template <class TargetTy>
class Controller : t_lib::Noncopyable<Controller<TargetTy>> {
public :
    using TargetType = TargetTy;

    Controller(TargetType* Target=nullptr) noexcept : target_{Target} {}
    virtual ~Controller() = default;

    ///
    /// \brief  この関数が呼び出された時点の入力状態で処理を行う
    ///
    virtual void run() = 0;

    ///
    /// \brief  操作対象をセット
    ///
    ///         デフォルトでは、操作対象を解除します。
    ///
    /// \param[in] Target : セットする操作対象
    ///
    void resetTarget(TargetType* Target=nullptr) noexcept { target_ = Target; }
    ///
    /// \brief  操作対象のアドレスを取得
    ///
    ///         nullptrが返却された場合、操作対象がいないことを表します。
    ///
    /// \return 操作対象のアドレス
    ///
    const TargetType* getTarget() const noexcept { return target_; }

protected :
    template <class RetTy, class ...FArgTypes, class ...ArgTypes>
    RetTy invoke(RetTy(TargetType::*Function)(FArgTypes...), ArgTypes&& ...Args) const {
        if(!target_) ctrler_impl::invokeError();
        return (target_->*Function)(std::forward<ArgTypes>(Args)...);
    }
    template <class RetTy, class ...FArgTypes, class ...ArgTypes>
    RetTy invoke(RetTy(TargetType::*Function)(FArgTypes...) const, ArgTypes&& ...Args) const {
        if(!target_) ctrler_impl::invokeError();
        return (target_->*Function)(std::forward<ArgTypes>(Args)...);
    }

private :
    TargetType* target_;
};

} // namespace i_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_ILIB_CONTROLLER_HEADER_
// EOF
