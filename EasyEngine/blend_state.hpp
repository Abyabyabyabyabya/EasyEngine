///
/// \file   blend_state.hpp
/// \brief  ブレンド状態定義クラス定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/9/4
///             - ヘッダ追加
///             - BlendState 定義
///             - BlendDesc 定義
///                 - BlendCoefficient 定義
///                 - BlendOperation 定義
///                 - OpaqueBlend 定義
///                 - AlphaBlend 定義
///                 - AddtiveBlend 定義
///                 - NonPremultipliedBlend 定義
///         - 2020/9/8
///             - プリセットを関数に置き換えた
///
#ifndef INCLUDED_EGEG_GLIB_BLEND_STATE_HEADER_
#define INCLUDED_EGEG_GLIB_BLEND_STATE_HEADER_

#include <array>
#include <d3d11.h>
#include <wrl.h>
#include "color.hpp"

namespace easy_engine {
namespace g_lib {

/******************************************************************************

    BlendDesc

******************************************************************************/
/// 入力に対する係数
// 詳細 : https://docs.microsoft.com/en-us/windows/win32/api/D3D11/ne-d3d11-d3d11_blend
enum class BlendCoefficient {
    kZero,
    kOne,
    kSrcColor,
    kInvSrcColor,
    kSrcAlpha,
    kInvSrcAlpha,
    kDestAlpha,
    kInvDestAlpha,
    kDestColor,
    kInvDestColor,
    kSrcAlphaSat,
    kBlendFactor,
    kInvBlendFactor,
    kSrc1Color,
    kInvSrc1Color,
    kSrc1Alpha,
    kInvSrc1Alpha	
};
/// ブレンド演算
// 詳細 : https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_blend_op
enum class BlendOperation {
    kAdd,
    kSubtract,
    kRevSubtract,
    kMin,
    kMax
};

struct BlendDesc {
    bool enable;                      ///< true:ブレンドあり　false : ブレンドなし
    BlendCoefficient src_coef;        ///< ソース色に対する係数
    BlendCoefficient dest_coef;       ///< 書き込み先の色に対する係数
    BlendOperation operation;         ///< ブレンド演算
    BlendCoefficient src_alpha_coef;  ///< ソースα値に対する係数
    BlendCoefficient dest_alpha_coef; ///< 書き込み先α値に対する係数
    BlendOperation alpha_operation;   ///< αブレンド演算
    ColorFlag write_color_mask;       ///< 書き込む色(ビットフラグ)
};


/******************************************************************************

    BlendState

******************************************************************************/
///
/// \brief  ブレンド状態定義クラス
///
class BlendState {
public :
    ///
    /// \brief  デフォルトのコンストラクタ
    ///
    ///         状態の定義を持ちません。
    ///
    BlendState() = default;

    ///
    /// \brief  ブレンドステートの作成を伴うコンストラクタ
    ///
    ///         第2引数には出力ターゲット毎のブレンド状態を設定できます。
    ///         複数のターゲットを設定する場合はstd::array<…>に格納して渡してください。
    ///
    /// \param[in] Desc : ブレンド状態定義構造体
    /// \param[in] AlphaToCaverageEnable : アルファトゥカヴァレッジ指定フラグ　true:有効　false:無効
    ///
    /// \attention 複数のターゲットを設定する際、設定できる最大数は8です。
    ///
    BlendState(const BlendDesc& Desc, bool AlphaToCaverageEnable=false);
    BlendState(const std::array<BlendDesc, 8U>& Descs, bool AlphaToCaverageEnable=false);

    ///
    /// \brief  有効なブレンド状態定義オブジェクトかどうか判定
    ///
    ///         true  : 有効
    ///         false : 無効
    ///
    /// \return 判定結果
    ///
    bool isValid() const noexcept { return state_; }
    operator bool() const noexcept { return isValid(); }


    /// ブレンドステートオブジェクトを取得
    ID3D11BlendState* state() const noexcept { return state_.Get(); }
private :
    Microsoft::WRL::ComPtr<ID3D11BlendState> state_;
};


/******************************************************************************

    blend presets

******************************************************************************/
// 参考 : https://github.com/microsoft/DirectXTK
//        https://github.com/microsoft/DirectXTK/blob/master/Src/CommonStates.cpp
  namespace blend_impl {
      inline BlendState createBlend(const bool E, const BlendCoefficient Src, const BlendCoefficient Dest, const BlendOperation Op) {
          return BlendState {
              BlendDesc {
                E,
                Src, Dest, Op,
                Src, Dest, Op,
                kColorBitMask<1,1,1,1>
              }
          };
      }
  }

namespace blend_presets {
/// ブレンド無し
inline BlendState opaque() { return blend_impl::createBlend(false, BlendCoefficient::kOne, BlendCoefficient::kZero, BlendOperation::kAdd); }
/// αブレンド
inline BlendState alpha() { return blend_impl::createBlend(true, BlendCoefficient::kOne, BlendCoefficient::kInvSrcAlpha, BlendOperation::kAdd); }
/// 加算合成
inline BlendState addtive() { return blend_impl::createBlend(true, BlendCoefficient::kSrcAlpha, BlendCoefficient::kOne, BlendOperation::kAdd); }
/// 事前乗算無し
inline BlendState nonPremultiplied() { return blend_impl::createBlend(true, BlendCoefficient::kSrcAlpha, BlendCoefficient::kInvSrcAlpha, BlendOperation::kAdd); }
} // namespace blend_preset

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_BLEND_STATE_HEADER_
// EOF
