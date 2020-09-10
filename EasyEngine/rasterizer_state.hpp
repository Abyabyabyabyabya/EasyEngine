///
/// \file   rasterizer_state.hpp
/// \brief  ラスタライザ状態定義クラス定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/9/8
///             - ヘッダ追加
///             - RasterizerState 定義
///             - RasterizerDesc 定義
///                 -
///
#ifndef INCLUDED_EGEG_GLIB_RASTERIZER_STATE_HEADER_
#define INCLUDED_EGEG_GLIB_RASTERIZER_STATE_HEADER_

#include <d3d11.h>
#include <wrl.h>

namespace easy_engine {
namespace g_lib {

/******************************************************************************

    RasterizerDesc

******************************************************************************/
/// 3角形をレンダリングするときの塗りつぶし方法
// 詳細 : https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_rasterizer_desc
enum class RasterizerFillMode {
    kWireframe,
    kSolid
};

/// 描画しない3角形の方向
// 詳細 : https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_rasterizer_desc
enum class RasterizerCullMode {
    kNone,
    kFront,
    kBack
};

/// 正面として扱う3角形の頂点の方向
enum class RasterizerFront {
    kCounterClockWise, ///< 反時計周りが正面
    kClockWise         ///< 時計回りが正面
};

struct RasterizerDesc {
    RasterizerFillMode fill_mode;   ///< 3角形の塗りつぶし方法
    RasterizerCullMode cull_mode;   ///< 描画しない3角形の指定
    RasterizerFront front;          ///< 正面として扱う3角形
    int depth_bias;                 ///< ピクセルに追加される深度値
    float depth_bias_clamp;         ///< 最大深度バイアス
    float slope_scaled_depth_bias;  ///< ピクセルの傾き
    bool depth_clip_enable;         ///< 距離に戻づいたクリッピングを有効にするか　true:有効　false:無効
    bool scissor_enable;            ///< シザー矩形化リングを有効にするか　true:有効　false:無効
    bool multisample_enable;        ///< マルチサンプルを有効にするか　true:有効　false:無効
    bool antialiased_line_enable;   ///< 線の描画にアンチエイリアスを使用するか(multisample_enableがfalseのときのみ)　true:有効　false:無効
};


/******************************************************************************

    RasterizerState

******************************************************************************/
///
/// \brief  ラスタライザ状態定義クラス
///         
class RasterizerState {
public :
    ///
    /// \brief  デフォルトのコンストラクタ
    ///
    ///         状態の定義を持ちません。
    ///
    RasterizerState() = default;

    ///
    /// \brief  ラスタライザステートの作成を伴うコンストラクタ
    ///
    /// \param[in] Desc : ラスタライザステートの状態定義構造体
    ///
    RasterizerState(const RasterizerDesc& Desc);

    ///
    /// \brief  有効なラスタライザ状態定義オブジェクトかどうか判定
    ///
    ///         true  : 有効
    ///         false : 無効
    ///
    bool isValid() const noexcept { return state_; }
    operator bool() const noexcept { return isValid(); }


    /// ラスタライザステートオブジェクトを取得
    ID3D11RasterizerState* state() const noexcept { state_.Get(); }
private :
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> state_;
};


/******************************************************************************

    rasterizer presets

******************************************************************************/
// 参考 : https://github.com/microsoft/DirectXTK
//        https://github.com/microsoft/DirectXTK/blob/master/Src/CommonStates.cpp
  namespace rasterizer_impl {
      inline RasterizerState createRS(const RasterizerFillMode F, const RasterizerCullMode C) {
          return RasterizerState {
              RasterizerDesc {
                F,
                C,
                RasterizerFront{},
                0, 0.0F, 0.0F,
                true,
                false,
                true,
                false
              }
          };
      }
  } // namespace rasterizer_impl

namespace rasterizer_preset {
/// fill:kSolid　cull:kNone
inline RasterizerState nonCulling() { return rasterizer_impl::createRS(RasterizerFillMode::kSolid, RasterizerCullMode::kNone); }
// fill:kSolid　cull:kBack
inline RasterizerState solid() { return rasterizer_impl::createRS(RasterizerFillMode::kSolid, RasterizerCullMode::kBack); }
// fill:kWireframe cull:kBack
inline RasterizerState wireframe() { return rasterizer_impl::createRS(RasterizerFillMode::kWireframe, RasterizerCullMode::kBack); }
// fill:kWireframe cull:kNone
inline RasterizerState nonCullingwireframe() { return rasterizer_impl::createRS(RasterizerFillMode::kWireframe, RasterizerCullMode::kNone); }
} // namespace rasterizer_preset

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_RASTERIZER_STATE_HEADER_
// EOF
