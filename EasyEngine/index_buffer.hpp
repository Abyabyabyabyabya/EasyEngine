///
/// \file   index_buffer.hpp
/// \brief  頂点インデックスバッファ定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/9/1
///             - ヘッダ追加
///             - IndexBuffer 定義
///
/// \note   IndexBuffer 必要性を感じないため、デフォルトのコンストラクタを定義していない。
///         必要に応じて定義してもよい。
///
#ifndef INCLUDED_EGEG_GLIB_INDEX_BUFFER_HEADER_
#define INCLUDED_EGEG_GLIB_INDEX_BUFFER_HEADER_

#include <cstdint>
#include <vector>
#include <d3d11.h>
#include <wrl.h>

namespace easy_engine {
namespace g_lib {

class IndexBuffer {
public :
    IndexBuffer(const std::vector<std::uint16_t>& Data) : 
      IndexBuffer{16U*Data.size(), D3D11_SUBRESOURCE_DATA{Data.data(), 0, 0}, DXGI_FORMAT::DXGI_FORMAT_R16_UINT} {}
    IndexBuffer(const std::vector<std::uint32_t>& Data) :
      IndexBuffer{32U*Data.size(), D3D11_SUBRESOURCE_DATA{Data.data(), 0, 0}, DXGI_FORMAT::DXGI_FORMAT_R32_UINT} {}

    ///
    /// \brief  有効な頂点インデックスバッファかどうか判定
    ///
    ///         true  : 有効
    ///         false : 無効
    ///
    /// \return 判定結果
    ///
    bool isValid() const noexcept { return ibuf_; }
    operator bool() const noexcept { return isValid(); }

    ///< バッファオブジェクトを取得
    ID3D11Buffer* buffer() const noexcept { return ibuf_.Get(); } 
    ///< インデックスフォーマットを取得
    DXGI_FORMAT format() const noexcept { return format_; }
protected :
    IndexBuffer(UINT, const D3D11_SUBRESOURCE_DATA&, DXGI_FORMAT);
private :
    Microsoft::WRL::ComPtr<ID3D11Buffer> ibuf_;
    DXGI_FORMAT format_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_INDEX_BUFFER_HEADER_
// EOF
