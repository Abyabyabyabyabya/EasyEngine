///
/// \file   sampler_state.hpp
/// \brief  サンプラー状態定義クラス定義ヘッダ
///
/// \aurhor 板場
///
/// \par    履歴
///         - 2020/9/4
///             - ヘッダ追加
///             - SamplerState 定義
///             - SamplerDesc 定義
///                 - SamplerFilter 定義
///                 - SamplerAddressMode 定義
///                 - SamplerComparison 定義
///                 - PointWrapSampler 定義
///                 - PointMirrorSampler 定義
///                 - PointClampSampler 定義
///                 - PointBorderSampler 定義
///                 - PointMirrorOnceSampler 定義
///                 - LinearWrapSampler 定義
///                 - LinearMirrorSampler 定義
///                 - LinearClampSampler 定義
///                 - LinearBorderSampler 定義
///                 - LinearMirrorOnceSampler 定義
///                 - AnisotropicWrapSampler 定義
///                 - AnisotropicMirrorSampler 定義
///                 - AnisotropicClampSampler 定義
///                 - AnisotropicBorderSampler 定義
///                 - AnisotropicMirrorOnceSampler 定義
///         - 2020/9/8
///             - プリセットを関数に置き換えた
///
#ifndef INCLUDED_EGEG_GLIB_SAMPLER_STATE_HEADER_
#define INCLUDED_EGEG_GLIB_SAMPLER_STATE_HEADER_

#include <cstdint>
#include <d3d11.h>
#include <wrl.h>
#include "color.hpp"

namespace easy_engine {
namespace g_lib {

/******************************************************************************

    SamplerDesc

******************************************************************************/
/// フィルタリング方法
// 詳細 : https://docs.microsoft.com/en-us/windows/win32/api/D3D11/ne-d3d11-d3d11_filter
enum class SamplerFilter {
    kMinMagMipPoint,
    kMinMagPointMipLinear,
    kMinPointMagLinearMipPoint,
    kMinPointMagMipLinear,
    kMinLinearMagMipPoint,
    kMinLinearMagPointMipLinear,
    kMinMagLinearMipPoint,
    kMinMagMipLinear,
    kAnisotropic,

    kComparisonMinMagMipPoint,
    kComparisonMinMagPointMipLinear,
    kComparisonMinPointMagLinearMipPoint,
    kComparisonMinPointMagMipLinear,
    kComparisonMinLinearMagMipPoint,
    kComparisoninLinearMagPointMipLinear,
    kComparisoninMagLinearMipPoint,
    kComparisoninMagMipLinear,
    kComparisonAnisotropic,

    kMinimumMinMagMipPoint,
    kMinimumMinMagPointMipLinear,
    kMinimumMinPointMagLinearMipPoint,
    kMinimumMinPointMagMipLinear,
    kMinimumMinLinearMagMipPoint,
    kMinimuminLinearMagPointMipLinear,
    kMinimuminMagLinearMipPoint,
    kMinimuminMagMipLinear,
    kMinimumAnisotropic,

    kMaximumMinMagMipPoint,
    kMaximumMinMagPointMipLinear,
    kMaximumMinPointMagLinearMipPoint,
    kMaximumMinPointMagMipLinear,
    kMaximumMinLinearMagMipPoint,
    kMaximuminLinearMagPointMipLinear,
    kMaximuminMagLinearMipPoint,
    kMaximuminMagMipLinear,
    kMaximumAnisotropic
};

/// テクスチャの範囲外になるuv座標の解決方法
// 詳細 : https://docs.microsoft.com/en-us/windows/win32/api/D3D11/ne-d3d11-d3d11_texture_address_mode
enum class SamplerAddressMode {
    kWrap,
    kMirror,
    kClamp,
    kBorder,
    kMirrorOnce
};

/// サンプリングされたデータと既存のサンプリング済みデータの比較操作
// 詳細 : https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_comparison_func
enum class SamplerComparison {
    kNever,
    kLess,
    kEqual,
    kLessEqual,
    kGreater,
    kNotEqual,
    kGreaterEqual,
    kAlways
};

struct SamplerDesc {
    SamplerFilter filter;         ///< テクスチャをサンプリングする際のフィルタリング方法
    SamplerAddressMode address_u; ///< 範囲外のテクスチャu座標の解決方法
    SamplerAddressMode address_v; ///< 範囲外のテクスチャv座標の解決方法
    SamplerAddressMode address_w; ///< 範囲外のテクスチャw座標の解決方法
    float mip_lod_bias;           ///< 計算されたみっぷマップレベルからのオフセット
    unsigned max_anisotropy;      ///< filterにkAnisotropicかkComparisonAnisotropicを指定した場合に使用されるクランプ値(1~16)
    SamplerComparison comparison; ///< サンプリング済みデータ比較オプション
    Color border_color;           ///< address_〇にkBorderを指定した場合に使用する境界線の色
    float min_lod;                ///< アクセスをクランプするミップマップの下限値
    float max_lod;                ///< アクセスをクランプするミップマップの上限値
};


/******************************************************************************

    SamplerState

******************************************************************************/
///
/// \brief  サンプラー状態定義クラス
///
class SamplerState {
public :
    ///
    /// \brief  デフォルトのコンストラクタ
    ///
    ///         状態の定義を持ちません。。
    ///
    SamplerState() = default;

    ///
    /// \brief  サンプラーステートの作成を伴うコンストラクタ
    ///
    /// \param[in] Desc : サンプラー状態定義構造体
    ///
    SamplerState(const SamplerDesc& Desc);

    ///
    /// \brief  有効なサンプラー状態定義オブジェクトかどうか判定
    ///
    ///         true  : 有効
    ///         false : 無効
    ///
    /// \return 判定結果
    ///
    bool isValid() const noexcept { return state_.Get(); }
    operator bool() const noexcept { return isValid(); }


    /// サンプラーステートオブジェクトを取得
    ID3D11SamplerState* state() const noexcept { return state_.Get(); }
private :
    Microsoft::WRL::ComPtr<ID3D11SamplerState> state_;
};


/******************************************************************************

    sampler presets

******************************************************************************/
// 参考 : https://github.com/microsoft/DirectXTK
//        https://github.com/microsoft/DirectXTK/blob/master/Src/CommonStates.cpp
  namespace sampler_impl { 
      inline SamplerState createSampler(const SamplerFilter F, const SamplerAddressMode A, const Color C=Color{0}) {
          return SamplerState {
              SamplerDesc {
                F,
                A, A, A,
                0.0F,
                D3D11_MAX_MAXANISOTROPY,
                SamplerComparison::kNever,
                Color{0},
                0.0F, D3D11_FLOAT32_MAX
              }
          };
      }
  } // namespace sampler_impl

namespace sampler_presets {
// point
inline SamplerState pointWrap() { return sampler_impl::createSampler(SamplerFilter::kMinMagMipPoint, SamplerAddressMode::kWrap); }
inline SamplerState pointMirror() { return sampler_impl::createSampler(SamplerFilter::kMinMagMipPoint, SamplerAddressMode::kMirror); }
inline SamplerState pointClamp() { return sampler_impl::createSampler(SamplerFilter::kMinMagMipPoint, SamplerAddressMode::kClamp); }
inline SamplerState pointBorder(const Color BorderColor) { return sampler_impl::createSampler(SamplerFilter::kMinMagMipPoint, SamplerAddressMode::kBorder, BorderColor); }
inline SamplerState pointMirrorOnce() { return sampler_impl::createSampler(SamplerFilter::kMinMagMipPoint, SamplerAddressMode::kMirrorOnce); }
// linear
inline SamplerState linearWrap() { return sampler_impl::createSampler(SamplerFilter::kMinMagMipLinear, SamplerAddressMode::kWrap); }
inline SamplerState linearMirror() { return sampler_impl::createSampler(SamplerFilter::kMinMagMipLinear, SamplerAddressMode::kMirror); }
inline SamplerState linearClamp() { return sampler_impl::createSampler(SamplerFilter::kMinMagMipLinear, SamplerAddressMode::kClamp); }
inline SamplerState linearBorder(const Color BorderColor) { return sampler_impl::createSampler(SamplerFilter::kMinMagMipLinear, SamplerAddressMode::kBorder, BorderColor);}
inline SamplerState linearMirrorOnce() { return sampler_impl::createSampler(SamplerFilter::kMinMagMipLinear, SamplerAddressMode::kMirrorOnce); }
// anisotropic
inline SamplerState anisotropicWrap() { return sampler_impl::createSampler(SamplerFilter::kAnisotropic, SamplerAddressMode::kWrap); }
inline SamplerState anisotropicMirror() { return sampler_impl::createSampler(SamplerFilter::kAnisotropic, SamplerAddressMode::kMirror); }
inline SamplerState anisotropicClamp() { return sampler_impl::createSampler(SamplerFilter::kAnisotropic, SamplerAddressMode::kClamp); }
inline SamplerState anisotropicBorder(const Color BorderColor) { return sampler_impl::createSampler(SamplerFilter::kAnisotropic, SamplerAddressMode::kBorder, BorderColor); }
inline SamplerState anisotropicMirrorOnce() { return sampler_impl::createSampler(SamplerFilter::kAnisotropic, SamplerAddressMode::kMirrorOnce); }
} // namespace sampler_presets

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_SAMPLER_STATE_HEADER_
// EOF
