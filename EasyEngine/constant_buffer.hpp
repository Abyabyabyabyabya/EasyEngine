///
/// \file   constant_buffer.hpp
/// \brief  �萔�o�b�t�@��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/8/28
///             - �w�b�_�ǉ�
///             - ConstantBufferData ��`
///             - ConstantBuffer<�c> ��`
///
#ifndef INCLUDED_EGEG_GLIB_CONSTANT_BUFFER_HEADER_
#define INCLUDED_EGEG_GLIB_CONSTANT_BUFFER_HEADER_

#include <d3d11.h>
#include <wrl.h>

namespace easy_engine {
namespace g_lib {
  namespace constant_buffer_impl {
    class ConstantBufferData { // ��e���v���[�g�����o
    public :
        ///
        /// \brief  �L���Ȓ萔�o�b�t�@���ǂ�������
        ///
        ///         true  : �L��
        ///         false : ����
        ///
        /// \return ���茋��
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
/// \brief  �萔�o�b�t�@
///
/// \tparam DataTy : �o�b�t�@�ɕێ�����f�[�^�^
///
template <class DataTy>
class ConstantBuffer : public constant_buffer_impl::ConstantBufferData {
public :
    ///
    /// \brief  �f�t�H���g�R���X�g���N�^
    ///
    ///         �����f�[�^�������Ȃ��o�b�t�@���쐬���A�ێ����܂��B
    ///
    ConstantBuffer() : ConstantBufferData{sizeof(DataTy), nullptr} {}

    ///
    /// \brief  �����f�[�^��^����R���X�g���N�^
    ///
    ///         �����̃f�[�^�����o�b�t�@���쐬���A�ێ����܂��B
    ///
    /// \param[in] InitialData : �o�b�t�@�̏����f�[�^
    ///
    ConstantBuffer(const DataTy& InitialData) :
      ConstantBufferData{sizeof(DataTy), &D3D11_SUBRESOURCE_DATA{&InitialData, 0U, 0U}} {}

    ///
    /// \brief  �o�b�t�@�̃f�[�^������������
    ///
    ///         �߂�l�ɏ��������̌��ʂ��i�[���܂��B
    ///         true  : ����
    ///         false : ���s
    ///
    /// \param[in] Data : �ύX��̃f�[�^
    ///
    /// \return ������������
    ///
    bool setData(const DataTy& Data) {
        return update(&Data, sizeof(DataTy));
    }
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_CONSTANT_BUFFER_HEADER_
// EOF
