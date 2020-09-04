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

/// サンプリングされたデータと既存のサンプリング済みデータの比較オプション
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

    Sampler Presets

******************************************************************************/
// 参考 : https://github.com/microsoft/DirectXTK
//        https://github.com/microsoft/DirectXTK/blob/master/Src/CommonStates.cpp

  namespace sampler_impl {
    struct SamplerPresetCommon : SamplerDesc {
        SamplerPresetCommon(
          const SamplerFilter Filter, const SamplerAddressMode AddressMode, const Color BorderColor=Color{0}) : 
            SamplerDesc {
              Filter,
              AddressMode,
              AddressMode,
              AddressMode,
              0.0F,
              D3D11_MAX_MAXANISOTROPY,
              SamplerComparison::kNever,
              Color{0},
              0.0F,
              D3D11_FLOAT32_MAX} {}
    };
  } // namespace sampler_impl

// ポイントラップ
struct PointWrapSampler : sampler_impl::SamplerPresetCommon {
    PointWrapSampler() : SamplerPresetCommon {SamplerFilter::kMinMagMipPoint, SamplerAddressMode::kWrap} {}
};
// ポイントミラー
struct PointMirrorSampler : sampler_impl::SamplerPresetCommon {
    PointMirrorSampler() : SamplerPresetCommon {SamplerFilter::kMinMagMipPoint, SamplerAddressMode::kMirror} {}
};
// ポイントクランプ
struct PointClampSampler : sampler_impl::SamplerPresetCommon {
    PointClampSampler() : SamplerPresetCommon {SamplerFilter::kMinMagMipPoint, SamplerAddressMode::kClamp} {}
};
// ポイントボーダー
struct PointBorderSampler : sampler_impl::SamplerPresetCommon {
    PointBorderSampler(const Color BorderColor=kWhite) : 
      SamplerPresetCommon {SamplerFilter::kMinMagMipPoint, SamplerAddressMode::kBorder, BorderColor} {}
};
// ポイントミラーワンス
struct PointMirrorOnceSampler : sampler_impl::SamplerPresetCommon {
    PointMirrorOnceSampler() : SamplerPresetCommon{SamplerFilter::kMinMagMipPoint, SamplerAddressMode::kMirrorOnce} {}
};

// リニアラップ
struct LinearWrapSampler : sampler_impl::SamplerPresetCommon {
    LinearWrapSampler() : SamplerPresetCommon {SamplerFilter::kMinMagMipLinear, SamplerAddressMode::kWrap} {}
};
// リニアミラー
struct LinearMirrorSampler : sampler_impl::SamplerPresetCommon {
    LinearMirrorSampler() : SamplerPresetCommon {SamplerFilter::kMinMagMipLinear, SamplerAddressMode::kMirror} {}
};
// リニアクランプ
struct LinearClampSampler : sampler_impl::SamplerPresetCommon {
    LinearClampSampler() : SamplerPresetCommon {SamplerFilter::kMinMagMipLinear, SamplerAddressMode::kClamp} {}
};
// リニアボーダー
struct LinearBorderSampler : sampler_impl::SamplerPresetCommon {
    LinearBorderSampler(const Color BorderColor=kWhite) :
      SamplerPresetCommon {SamplerFilter::kMinMagMipLinear, SamplerAddressMode::kBorder, BorderColor} {}
};
// リニアミラーワンス
struct LinearMirrorOnceSampler : sampler_impl::SamplerPresetCommon {
    LinearMirrorOnceSampler() : SamplerPresetCommon{SamplerFilter::kMinMagMipLinear, SamplerAddressMode::kMirrorOnce}{}
};

// アニソトロピックラップ
struct AnisotropicWrapSampler : sampler_impl::SamplerPresetCommon {
    AnisotropicWrapSampler() : SamplerPresetCommon {SamplerFilter::kAnisotropic, SamplerAddressMode::kWrap} {}
};
// アニソトロピックミラー
struct AnisotropicMirrorSampler : sampler_impl::SamplerPresetCommon {
    AnisotropicMirrorSampler() : SamplerPresetCommon {SamplerFilter::kAnisotropic, SamplerAddressMode::kMirror} {}
};
// アニソトロピッククランプ
struct AnisotropicClampSampler : sampler_impl::SamplerPresetCommon {
    AnisotropicClampSampler() : SamplerPresetCommon {SamplerFilter::kAnisotropic, SamplerAddressMode::kClamp} {}
};
// アニソトロピックボーダー
struct AnisotropicBorderSampler : sampler_impl::SamplerPresetCommon {
    AnisotropicBorderSampler(const Color BorderColor=kWhite) :
      SamplerPresetCommon {SamplerFilter::kAnisotropic, SamplerAddressMode::kBorder, BorderColor} {}
};
// アニソトロピックミラーワンス
struct AnisotropicMirrorOnceSampler : sampler_impl::SamplerPresetCommon {
    AnisotropicMirrorOnceSampler() : SamplerPresetCommon{SamplerFilter::kAnisotropic,SamplerAddressMode::kMirrorOnce}{}
};

using DefaultSampler = LinearClampSampler; ///< デフォルトのサンプラー


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
    /// \brief  有効なサンプラー状態定義クラスかどうか判定
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

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_SAMPLER_STATE_HEADER_
// EOF
