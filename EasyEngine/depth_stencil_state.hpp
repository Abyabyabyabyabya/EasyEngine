///
/// \file   depth_stencil_state.hpp
/// \brief  深度ステンシル状態定義クラス定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/9/4
///             - ヘッダ追加
///
#ifndef INCLUDED_EGEG_GLIB_DEPTH_STENCIL_STATE_HEADER_
#define INCLUDED_EGEG_GLIB_DEPTH_STENCIL_STATE_HEADER_

#include <d3d11.h>
#include <wrl.h>

namespace easy_engine {
namespace g_lib {

/******************************************************************************

    DepthStencilDesc

******************************************************************************/
enum class StencilOperation {
};

/// 深度データと既存の深度データの比較オプション
enum class DepthStencilComparison {

};

struct DepthStencilDesc {

};


/******************************************************************************

    DepthStencilState

******************************************************************************/
///
/// \brief  深度ステンシル状態定義クラス
///
class DepthStencilState {
public :
    ///
    /// \brief  デフォルトのコンストラクタ
    ///
    ///         状態の定義を持ちません。
    ///
    DepthStencilState() = default;

    ///
    /// \brief  有効な深度ステンシル状態定義クラスかどうか判定
    ///
    ///         true  : 有効
    ///         false : 無効
    ///
    /// \return 判定結果
    ///
    bool isValid() const noexcept { return state_; }
    operator bool() const noexcept { return isValid(); }

    /// 深度ステンシルステートオブジェクトを取得
    ID3D11DepthStencilState* state() const noexcept { state_.Get(); }
private :
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> state_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_DEPTH_STENCIL_STATE_HEADER_
// EOF
