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

/******************************************************************************

    IndexBuffer

******************************************************************************/
///
/// \brief  ���_�C���f�b�N�X�o�b�t�@
///
class IndexBuffer {
public :
    ///
    /// \brief  �f�t�H���g�̃R���X�g���N�^
    ///
    ///         �o�b�t�@�͐������܂���B
    ///
    IndexBuffer() = default;

    ///
    /// \brief  �o�b�t�@�𐶐�����R���X�g���N�^
    ///
    ///         �����̃f�[�^�����o�b�t�@�𐶐����܂��B
    ///         �C���f�b�N�X��\���^�̃T�C�Y��16bit�ł��B
    ///
    IndexBuffer(const std::vector<std::uint16_t>& Data) : 
      IndexBuffer{16U*Data.size(), D3D11_SUBRESOURCE_DATA{Data.data(), 0, 0}, DXGI_FORMAT::DXGI_FORMAT_R16_UINT} {}
    ///
    /// \brief  �o�b�t�@�𐶐�����R���X�g���N�^
    ///
    ///         �����̃f�[�^�����o�b�t�@�𐶐����܂��B
    ///         �C���f�b�N�X��\���^�̃T�C�Y��32bit�ł��B
    ///
    IndexBuffer(const std::vector<std::uint32_t>& Data) :
      IndexBuffer{32U*Data.size(), D3D11_SUBRESOURCE_DATA{Data.data(), 0, 0}, DXGI_FORMAT::DXGI_FORMAT_R32_UINT} {}

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

    /// �o�b�t�@�I�u�W�F�N�g���擾
    ID3D11Buffer* buffer() const noexcept { return ibuf_.Get(); } 
    /// �C���f�b�N�X�t�H�[�}�b�g���擾
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
