///
/// \file   texture_resource.hpp
/// \brief  テクスチャリソース定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/9/2
///             - ヘッダ追加
///             - TextureResource 定義
///
#ifndef INCLUDED_EGEG_GLIB_TEXTURE_RESOURCE_HEADER_
#define INCLUDED_EGEG_GLIB_TEXTURE_RESOURCE_HEADER_

#include <d3d11.h>
#include <wrl.h>

namespace easy_engine {
namespace g_lib {

/******************************************************************************

    TextureResource

******************************************************************************/
///
/// \brief  テクスチャリソース
///
class TextureResource {
public :
    virtual ~TextureResource() = default;

    ///
    /// \brief  デフォルトのコンストラクタ
    ///
    ///         テクスチャは作成しません。
    ///
    TextureResource() = default;

    ///
    /// \brief  テクスチャの作成を伴うコンストラクタ
    ///
    /// \param[in] テクスチャの定義
    /// \param[in] テクスチャの初期データ(省略で初期データなし)
    ///
    TextureResource(const D3D11_TEXTURE2D_DESC&, const D3D11_SUBRESOURCE_DATA&);
    TextureResource(const D3D11_TEXTURE2D_DESC&);

    ///
    /// \brief  有効なテクスチャリソースかどうか判定
    ///
    ///         true  : 有効
    ///         false : 無効
    ///
    /// \return 判定結果
    ///
    bool isValid() const noexcept { return resource_; }
    operator bool() const noexcept { return isValid(); }


    /// リソースを取得
    ID3D11Texture2D* resource() const noexcept { return resource_.Get(); }
protected :
    Microsoft::WRL::ComPtr<ID3D11Texture2D> resource_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_TEXTURE_RESOURCE_HEADER_
// EOF
