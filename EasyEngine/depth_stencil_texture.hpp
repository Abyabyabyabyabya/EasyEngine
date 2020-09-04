///
/// \file   depth_stencil_texture.hpp
/// \brief  深度ステンシル用テクスチャ定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/9/2
///             - ヘッダ追加
///             - DepthStencilTexture 定義
///
#ifndef INCLUDED_EGEG_GLIB_DEPTH_STENCIL_TEXTURE_HEADER_
#define INCLUDED_EGEG_GLIB_DEPTH_STENCIL_TEXTURE_HEADER_

#include "texture_resource.hpp"

namespace easy_engine {
namespace g_lib {

/******************************************************************************

    DepthStencilTexture

******************************************************************************/
///
/// \brief  深度ステンシル用テクスチャ
///
class DepthStencilTexture : public TextureResource {
public :
    ///
    /// \enum   Format
    /// \brief  テクスチャフォーマット
    ///
    ///         詳細はMicrosoft DXGI_FORMAT enumerationを参照してください。
    ///         https://docs.microsoft.com/en-us/windows/win32/api/dxgiformat/ne-dxgiformat-dxgi_format
    ///
    enum class Format {
        kD32FloatS8X24Uint,
        kD32Float,
        kD24UnormS8Uint,
        kD16Unorm
    };

    DepthStencilTexture() = default;

    ///
    /// \brief  テクスチャの作成を伴うコンストラクタ
    ///
    /// \param[in] Width         : テクスチャ横幅
    /// \param[in] Height        : テクスチャ縦幅
    /// \param[in] Format        : テクスチャフォーマット
    /// \param[in] SampleCount   : 1ピクセル当たりのサンプル数
    /// \param[in] SampleQuality : マルチサンプルの画質レベル
    ///
    DepthStencilTexture(unsigned Width, unsigned Height, Format TextureFormat=Format::kD32Float, UINT SampleCount=1U, UINT SampleQuality=0U);

    ///
    /// \brief  有効な深度ステンシルテクスチャかどうか判定
    ///
    ///         true  : 有効
    ///         false : 無効
    ///
    bool isValid() const noexcept { return TextureResource::isValid() && texture_; }
    operator bool() const noexcept { return isValid(); }


    /// テクスチャを取得
    ID3D11DepthStencilView* texture() const noexcept { return texture_.Get(); }
private :
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> texture_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_DEPTH_STENCIL_TEXTURE_HEADER_
// EOF
