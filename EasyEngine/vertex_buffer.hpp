///
/// \file   vertex_buffer.hpp
/// \brief  頂点バッファ定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/9/1
///             - ヘッダ追加
///             - VertexBuffer 定義
///
/// \note   VertexBuffer 必要性を感じないため、デフォルトのコンストラクタを定義していない。
///         必要に応じて定義してもよい。
///
#ifndef INCLUDED_EGEG_GLIB_VERTEX_BUFFER_HEADER_
#define INCLUDED_EGEG_GLIB_VERTEX_BUFFER_HEADER_

#include <vector>
#include <d3d11.h>
#include <wrl.h>

namespace easy_engine {
namespace g_lib {

///
/// \class  VertexBuffer
/// \brief  頂点バッファ
///
class VertexBuffer {
public :
    ///
    /// \brief  デフォルトのコンストラクタ
    ///
    ///         バッファは作成しません。
    ///
    VertexBuffer() = default;

    ///
    /// \brief  バッファの作成を伴うコンストラクタ
    ///
    ///         引数のデータで初期化したバッファを保持します。
    ///
    /// \param[in] Data : データ
    ///
    template <class DataTy>
    VertexBuffer(const std::vector<DataTy>& Data) :
      VertexBuffer{sizeof(DataTy)*Data.size(), D3D11_SUBRESOURCE_DATA{Data.data(), 0, 0}, sizeof(DataTy)} {}

    ///
    /// \brief  有効な頂点バッファかどうか判定
    ///
    ///         true  : 有効
    ///         false : 無効
    ///
    /// \return 判定結果
    ///
    bool isValid() const noexcept { return vbuf_; }
    operator bool() const noexcept { return isValid(); }


    ///< バッファオブジェクトを取得
    ID3D11Buffer* buffer() const noexcept { return vbuf_.Get(); }
    ///< 1要素のサイズを取得
    UINT stride() const noexcept { return stride_; }
private :
    VertexBuffer(UINT, const D3D11_SUBRESOURCE_DATA&, UINT);
    
    Microsoft::WRL::ComPtr<ID3D11Buffer> vbuf_;
    UINT stride_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_VERTEX_BUFFER_HEADER_
// EOF
