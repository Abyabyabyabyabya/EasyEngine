///
/// \file   depth_stencil_texture.hpp
/// \brief  �[�x�X�e���V���p�e�N�X�`����`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/9/2
///             - �w�b�_�ǉ�
///             - DepthStencilTexture ��`
///
#ifndef INCLUDED_EGEG_GLIB_DEPTH_STENCIL_TEXTURE_HEADER_
#define INCLUDED_EGEG_GLIB_DEPTH_STENCIL_TEXTURE_HEADER_

#include "texture_resource.hpp"

namespace easy_engine {
namespace g_lib {

/******************************************************************************

    DepthStencilTexture

******************************************************************************/
///
/// \brief  �[�x�X�e���V���p�e�N�X�`��
///
class DepthStencilTexture : public TextureResource {
public :
    ///
    /// \enum   Format
    /// \brief  �e�N�X�`���t�H�[�}�b�g
    ///
    ///         �ڍׂ�Microsoft DXGI_FORMAT enumeration���Q�Ƃ��Ă��������B
    ///         https://docs.microsoft.com/en-us/windows/win32/api/dxgiformat/ne-dxgiformat-dxgi_format
    ///
    enum class Format {
        kD32FloatS8X24Uint,
        kD32Float,
        kD24UnormS8Uint,
        kD16Unorm
    };

    DepthStencilTexture() = default;

    ///
    /// \brief  �e�N�X�`���̍쐬�𔺂��R���X�g���N�^
    ///
    /// \param[in] Width         : �e�N�X�`������
    /// \param[in] Height        : �e�N�X�`���c��
    /// \param[in] Format        : �e�N�X�`���t�H�[�}�b�g
    /// \param[in] SampleCount   : 1�s�N�Z��������̃T���v����
    /// \param[in] SampleQuality : �}���`�T���v���̉掿���x��
    ///
    DepthStencilTexture(unsigned Width, unsigned Height, Format TextureFormat=Format::kD32Float, UINT SampleCount=1U, UINT SampleQuality=0U);

    ///
    /// \brief  �L���Ȑ[�x�X�e���V���e�N�X�`�����ǂ�������
    ///
    ///         true  : �L��
    ///         false : ����
    ///
    bool isValid() const noexcept { return TextureResource::isValid() && texture_; }
    operator bool() const noexcept { return isValid(); }


    /// �e�N�X�`�����擾
    ID3D11DepthStencilView* texture() const noexcept { return texture_.Get(); }
private :
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> texture_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_DEPTH_STENCIL_TEXTURE_HEADER_
// EOF
