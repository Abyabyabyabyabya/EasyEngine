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
#ifndef INCLUDED_EGEG_GLIB_INDEX_BUFFER_HEADER_
#define INCLUDED_EGEG_GLIB_INDEX_BUFFER_HEADER_

#include <cstdint>
#include <vector>
#include <d3d11.h>
#include <wrl.h>

namespace easy_engine {
namespace g_lib {
  namespace index_buffer_impl {
    class IndexBufferData {
    public :
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

        ID3D11Buffer* buffer() const noexcept { return ibuf_.Get(); } 
        DXGI_FORMAT format() const noexcept { return format_; }
    protected :
        IndexBufferData(UINT, const D3D11_SUBRESOURCE_DATA&, DXGI_FORMAT);
    private :
        Microsoft::WRL::ComPtr<ID3D11Buffer> ibuf_;
        DXGI_FORMAT format_;
    };
    
    template <class T=std::uint32_t> 
    class IndexBuffer : public index_buffer_impl::IndexBufferData {
    public :
        IndexBuffer(const std::vector<T>& Data);
    };
  } // namespace index_buffer_impl

using IndexBuffer32 = index_buffer_impl::IndexBuffer<std::uint32_t>;
using IndexBuffer16 = index_buffer_impl::IndexBuffer<std::uint16_t>;

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_INDEX_BUFFER_HEADER_
// EOF
