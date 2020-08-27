///
/// \file   layer.hpp
/// \brief  レイヤー定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/27
///             - ヘッダ追加
///             - Layer 定義
///
#ifndef INCLUDED_EGEG_GLIB_LAYER_HEADER_
#define INCLUDED_EGEG_GLIB_LAYER_HEADER_

#include "texture.hpp"

namespace easy_engine {
namespace g_lib {

///
/// \class  Layer
/// \brief  レイヤー(シェーダーリソース & レンダーターゲット)
///
class Layer : public Texture {
public :
    Layer() = default;

    ///
    /// \brief  コンストラクタ
    ///
    /// \param[in] Width         : レイヤー横幅
    /// \param[in] Height        : レイヤー縦幅
    /// \param[in] SampleCount   : 1ピクセル当たりのサンプル数
    /// \param[in] SampleQuality : マルチサンプルの画質レベル
    ///
    Layer(UINT Width, UINT Height, UINT SampleCount=1U, UINT SampleQuality=0U);

    ///
    /// \brief  有効なレイヤーかどうか判定
    ///
    ///         true  : 有効
    ///         false : 無効
    ///
    /// \return 判定結果
    ///
    bool isValid() const noexcept {
        return Texture::isValid() && layer_;
    }
    operator bool() const noexcept {
        return isValid();
    }


    ///< レイヤーを取得
    ID3D11RenderTargetView* layer() const noexcept { layer_.Get(); }
protected :
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> layer_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_LAYER_HEADER_
// EOF
