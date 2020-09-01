///
/// \file   vertex_buffer.hpp
/// \brief  ���_�o�b�t�@��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/9/1
///             - �w�b�_�ǉ�
///             - VertexBuffer ��`
///
/// \note   VertexBuffer �K�v���������Ȃ����߁A�f�t�H���g�̃R���X�g���N�^���`���Ă��Ȃ��B
///         �K�v�ɉ����Ē�`���Ă��悢�B
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
/// \brief  ���_�o�b�t�@
///
class VertexBuffer {
public :
    ///
    /// \brief  �f�t�H���g�̃R���X�g���N�^
    ///
    ///         �o�b�t�@�͍쐬���܂���B
    ///
    VertexBuffer() = default;

    ///
    /// \brief  �o�b�t�@�̍쐬�𔺂��R���X�g���N�^
    ///
    ///         �����̃f�[�^�ŏ����������o�b�t�@��ێ����܂��B
    ///
    /// \param[in] Data : �f�[�^
    ///
    template <class DataTy>
    VertexBuffer(const std::vector<DataTy>& Data) :
      VertexBuffer{sizeof(DataTy)*Data.size(), D3D11_SUBRESOURCE_DATA{Data.data(), 0, 0}, sizeof(DataTy)} {}

    ///
    /// \brief  �L���Ȓ��_�o�b�t�@���ǂ�������
    ///
    ///         true  : �L��
    ///         false : ����
    ///
    /// \return ���茋��
    ///
    bool isValid() const noexcept { return vbuf_; }
    operator bool() const noexcept { return isValid(); }


    ///< �o�b�t�@�I�u�W�F�N�g���擾
    ID3D11Buffer* buffer() const noexcept { return vbuf_.Get(); }
    ///< 1�v�f�̃T�C�Y���擾
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
