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

#include <cstdint>
#include <d3d11.h>
#include <wrl.h>

namespace easy_engine {
namespace g_lib {

/******************************************************************************

    DepthStencilDesc

******************************************************************************/
/// 深度ステンシルテスト中に実行するステンシル操作
// 詳細 : https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_stencil_op
enum class StencilOperation {
    kKeep,
    kZero,
    kReplace,
    kIncrementSat,
    kDecrementSat,
    kInvert,
    kIncrement,
    kDecrement
};

/// 深度データと既存の深度データの比較オプション
// 詳細 : https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_comparison_func
enum class DepthStencilComparison {
    kNever,
    kLess,
    kEqual,
    kLessEqual,
    kGreater,
    kNotEqual,
    kGreaterEqual,
    kAlways
};

/// ステンシルテストの結果に基づいて実行するステンシル操作
struct StencilOperationDesc {
    StencilOperation fail;       ///< ステンシルテストが失敗した場合に実行する操作
    StencilOperation depth_fail; ///< ステンシルテストを通過、深度テストに失敗した場合に実行する操作
    StencilOperation pass;       ///< ステンシルテスト、深度テストの両方を通過した場合に実行する操作
    DepthStencilComparison func; ///< テスト結果と既にあるデータとの比較操作
};

struct DepthStencilDesc {
    bool depth_enable;                 ///< 深度テストの有無　true:有効　false:無効
    bool depth_write_enable;           ///< 深度値書き込みの有無　true:有効　false:無効
    DepthStencilComparison depth_func; ///< 深度テスト結果と既にあるデータとの比較操作
    bool stencil_enable;               ///< ステンシルテストの有無　true:有効　false:無効
    std::uint8_t stencil_read_mask;    ///< ステンシルデータを読み込むためのマスク
    std::uint8_t stencil_write_mask;   ///< ステンシルデータを書き込むためのマスク
    StencilOperationDesc front_face;   ///< 表面法線がカメラの方向を向いているピクセルの、テスト結果の使用方法
    StencilOperationDesc back_face;    ///< 表面法線がカメラから離れた方向を向いているピクセルの、テスト結果の使用方法
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
    /// \brief  深度ステンシルステートの作成を伴うコンストラクタ
    ///
    /// \param[in] Desc : 深度ステンシルの状態定義構造体
    ///
    DepthStencilState(const DepthStencilDesc& Desc);

    ///
    /// \brief  有効な深度ステンシル状態定義オブジェクトかどうか判定
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


/******************************************************************************

    depth-stencil presets

******************************************************************************/
// 参考 : https://github.com/microsoft/DirectXTK
//        https://github.com/microsoft/DirectXTK/blob/master/Src/CommonStates.cpp
  namespace depth_stencil_impl {
      inline DepthStencilState createDS(const bool E, const bool W) {
          return DepthStencilState {
              DepthStencilDesc {
                E,
                W, DepthStencilComparison::kLessEqual,
                false, D3D11_DEFAULT_STENCIL_READ_MASK, D3D11_DEFAULT_STENCIL_WRITE_MASK,
                StencilOperationDesc {StencilOperation::kKeep, StencilOperation::kKeep, StencilOperation::kKeep, DepthStencilComparison::kAlways},
                StencilOperationDesc {StencilOperation::kKeep, StencilOperation::kKeep, StencilOperation::kKeep, DepthStencilComparison::kAlways}
              }
          };
      }
  } // namespace depth_stencil_impl

namespace depth_stencil_preset {
/// 深度テスト、ステンシルテスト無し
inline DepthStencilState none() { return depth_stencil_impl::createDS(false, false); }
/// 深度テストあり、ステンシルテスト無し。深度値書き込みなし
inline DepthStencilState read() { return depth_stencil_impl::createDS(true, false); }
/// 深度テストあり、ステンシルテスト無し。深度値書き込みあり
inline DepthStencilState write() { return depth_stencil_impl::createDS(true, true); }
} // namespace depth_stencil_preset

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_DEPTH_STENCIL_STATE_HEADER_
// EOF
