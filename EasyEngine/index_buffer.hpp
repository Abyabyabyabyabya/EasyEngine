///
/// \file   index_buffer.hpp
/// \brief  ���_�C���f�b�N�X�o�b�t�@��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/9/1
///             - �w�b�_�ǉ�
///             - IndexBuffer ��`
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
        /// \brief  �L���Ȓ��_�C���f�b�N�X�o�b�t�@���ǂ�������
        ///
        ///         true  : �L��
        ///         false : ����
        ///
        /// \return ���茋��
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
