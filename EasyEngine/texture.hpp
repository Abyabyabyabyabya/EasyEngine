//
/// \file   texture.hpp
/// \brief  テクスチャハンドラ定義ヘッダ
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

#include <type_traits>
#include <d3d11.h>
#include <wrl.h>

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
class Texture {
public :
    Texture() = default;
    
    ///
    /// \brief  読み込みを伴う構築
    ///
    /// \tparam StrTy : 文字列型
    /// \param[in] FilePath : 読み込む画像のファイルパス
    ///
    template <class StrTy>
    Texture(StrTy&& FilePath) {
        load(std::forward<StrTy>(FilePath));
    }

    ///
    /// \brief  有効なテクスチャかどうか判定
    ///
    ///         true  : 有効
    ///         false : 無効
    ///
    /// \return 判定結果
    ///
    bool isValid() const noexcept {
        return view_;
    }
    operator bool() const noexcept {
        return isValid();
    }

    ///< リソースを取得
    ID3D11Texture2D* resource() const noexcept { return resource_.Get(); }
    ///< ビューを取得
    ID3D11ShaderResourceView* view() const noexcept { return view_.Get(); }

private :
    void load(const char*);
    Microsoft::WRL::ComPtr<ID3D11Texture2D> resource_;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> view_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_TEXTURE_HEADER_
// EOF
