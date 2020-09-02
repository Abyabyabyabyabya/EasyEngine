//
/// \file   texture.hpp
/// \brief  テクスチャ定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/24
///             - ヘッダ追加
///             - Texture 定義
///
#ifndef INCLUDED_EGEG_GLIB_TEXTURE_HEADER_
#define INCLUDED_EGEG_GLIB_TEXTURE_HEADER_

#include "texture_resource.hpp"

namespace easy_engine {
namespace g_lib {

///
/// \class  Texture
/// \brief  テクスチャ(シェーダーリソース)
///
///         コンストラクタで指定した画像ファイルをテクスチャとして保持します。
///         ファイル名を指定してコンストラクタを呼び出した場合、読み込み処理が発生します。
///
/// \par    読み込みを遅延させたい場合
///         - デフォルトコンストラクタで構築したテクスチャに代入
///           Texture texture{};
///             …
///           texture = Texture{"hogehoge.png"};
///
class Texture : public TextureResource {
public :
    Texture() = default;
    virtual ~Texture() = default;
    
    ///
    /// \brief  読み込みを伴う構築
    ///
    /// \param[in] FilePath : 読み込む画像のファイルパス
    ///
    Texture(const char* FilePath);

    ///
    /// \brief  有効なテクスチャかどうか判定
    ///
    ///         true  : 有効
    ///         false : 無効
    ///
    /// \return 判定結果
    ///
    bool isValid() const noexcept { return TextureResource::isValid() && texture_; }
    operator bool() const noexcept { return isValid(); }

    ///< テクスチャを取得
    ID3D11ShaderResourceView* texture() const noexcept { return texture_.Get(); }
protected :
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_TEXTURE_HEADER_
// EOF
