///
/// \file   constant_buffer.hpp
/// \brief  定数バッファ定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/28
///             - ヘッダ追加
///             - ConstantBufferData 定義
///             - ConstantBuffer<…> 定義
///
#ifndef INCLUDED_EGEG_GLIB_CONSTANT_BUFFER_HEADER_
#define INCLUDED_EGEG_GLIB_CONSTANT_BUFFER_HEADER_

#include <d3d11.h>
#include <wrl.h>

namespace easy_engine {
namespace g_lib {
  namespace constant_buffer_impl {
    class ConstantBufferData { // 非テンプレート部抽出
    public :
        ///
        /// \brief  有効な定数バッファかどうか判定
        ///
        ///         true  : 有効
        ///         false : 無効
        ///
        /// \return 判定結果
        ///
        bool isValid() const noexcept { return cbuf_; }
        operator bool() const noexcept { return isValid(); }


        ID3D11Buffer* buffer() const noexcept { return cbuf_.Get(); }

    protected :
        ConstantBufferData(UINT DataSize, const D3D11_SUBRESOURCE_DATA* InitialData);
        bool update(const void* Data, size_t Size);
    private: 
        Microsoft::WRL::ComPtr<ID3D11Buffer> cbuf_;
    };
  } // namespace constant_buffer_impl

///
/// \class  ConstantBuffer
/// \brief  定数バッファ
///
/// \tparam DataTy : バッファに保持するデータ型
///
template <class DataTy>
class ConstantBuffer : public constant_buffer_impl::ConstantBufferData {
public :
    ///
    /// \brief  デフォルトコンストラクタ
    ///
    ///         初期データを持たないバッファを作成し、保持します。
    ///
    ConstantBuffer() : ConstantBufferData{sizeof(DataTy), nullptr} {}

    ///
    /// \brief  初期データを与えるコンストラクタ
    ///
    ///         引数のデータを持つバッファを作成し、保持します。
    ///
    /// \param[in] InitialData : バッファの初期データ
    ///
    ConstantBuffer(const DataTy& InitialData) :
      ConstantBufferData{sizeof(DataTy), &D3D11_SUBRESOURCE_DATA{&InitialData, 0U, 0U}} {}

    ///
    /// \brief  バッファのデータを書き換える
    ///
    ///         戻り値に書き換えの結果を格納します。
    ///         true  : 成功
    ///         false : 失敗
    ///
    /// \param[in] Data : 変更後のデータ
    ///
    /// \return 書き換え結果
    ///
    bool setData(const DataTy& Data) {
        return update(&Data, sizeof(DataTy));
    }
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_CONSTANT_BUFFER_HEADER_
// EOF
