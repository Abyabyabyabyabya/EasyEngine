///
/// \file   layer.hpp
/// \brief  ���C���[��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/8/27
///             - �w�b�_�ǉ�
///             - Layer ��`
///
#ifndef INCLUDED_EGEG_GLIB_LAYER_HEADER_
#define INCLUDED_EGEG_GLIB_LAYER_HEADER_

#include "texture.hpp"

namespace easy_engine {
namespace g_lib {

///
/// \class  Layer
/// \brief  ���C���[(�V�F�[�_�[���\�[�X & �����_�[�^�[�Q�b�g)
///
class Layer : public Texture {
public :
    ///
    /// \enum   Format
    /// \brief  �e�N�X�`���t�H�[�}�b�g
    ///
    ///         �ڍׂ�Microsoft DXGI_FORMAT enumeration���Q�Ƃ��Ă��������B
    ///         https://docs.microsoft.com/en-us/windows/win32/api/dxgiformat/ne-dxgiformat-dxgi_format
    ///
    enum class Format : UINT {
        UNKNOWN,
        R32G32B32A32_TYPELESS,
        R32G32B32A32_FLOAT,
        R32G32B32A32_UINT,
        R32G32B32A32_SINT,
        R32G32B32_TYPELESS,
        R32G32B32_FLOAT,
        R32G32B32_UINT,
        R32G32B32_SINT,
        R16G16B16A16_TYPELESS,
        R16G16B16A16_FLOAT,
        R16G16B16A16_UNORM,
        R16G16B16A16_UINT,
        R16G16B16A16_SNORM,
        R16G16B16A16_SINT,
        R32G32_TYPELESS,
        R32G32_FLOAT,
        R32G32_UINT,
        R32G32_SINT,
        R32G8X24_TYPELESS,
        R32_FLOAT_X8X24_TYPELESS,
        X32_TYPELESS_G8X24_UINT,
        R10G10B10A2_TYPELESS,
        R10G10B10A2_UNORM,
        R10G10B10A2_UINT,
        R11G11B10_FLOAT,
        R8G8B8A8_TYPELESS,
        R8G8B8A8_UNORM,
        R8G8B8A8_UNORM_SRGB,
        R8G8B8A8_UINT,
        R8G8B8A8_SNORM,
        R8G8B8A8_SINT,
        R16G16_TYPELESS,
        R16G16_FLOAT,
        R16G16_UNORM,
        R16G16_UINT,
        R16G16_SNORM,
        R16G16_SINT,
        R32_TYPELESS,
        R32_FLOAT,
        R32_UINT,
        R32_SINT,
        R24G8_TYPELESS,
        R24_UNORM_X8_TYPELESS,
        X24_TYPELESS_G8_UINT,
        R8G8_TYPELESS,
        R8G8_UNORM,
        R8G8_UINT,
        R8G8_SNORM,
        R8G8_SINT,
        R16_TYPELESS,
        R16_FLOAT,
        R16_UNORM,
        R16_UINT,
        R16_SNORM,
        R16_SINT,
        R8_TYPELESS,
        R8_UNORM,
        R8_UINT,
        R8_SNORM,
        R8_SINT,
        A8_UNORM,
        R1_UNORM,
        R9G9B9E5_SHAREDEXP,
        R8G8_B8G8_UNORM,
        G8R8_G8B8_UNORM,
        BC1_TYPELESS,
        BC1_UNORM,
        BC1_UNORM_SRGB,
        BC2_TYPELESS,
        BC2_UNORM,
        BC2_UNORM_SRGB,
        BC3_TYPELESS,
        BC3_UNORM,
        BC3_UNORM_SRGB,
        BC4_TYPELESS,
        BC4_UNORM,
        BC4_SNORM,
        BC5_TYPELESS,
        BC5_UNORM,
        BC5_SNORM,
        B5G6R5_UNORM,
        B5G5R5A1_UNORM,
        B8G8R8A8_UNORM,
        B8G8R8X8_UNORM,
        R10G10B10_XR_BIAS_A2_UNORM,
        B8G8R8A8_TYPELESS,
        B8G8R8A8_UNORM_SRGB,
        B8G8R8X8_TYPELESS,
        B8G8R8X8_UNORM_SRGB,
        BC6H_TYPELESS,
        BC6H_UF16,
        BC6H_SF16,
        BC7_TYPELESS,
        BC7_UNORM,
        BC7_UNORM_SRGB,
        B4G4R4A4_UNORM,
    };

    Layer() = default;

    ///
    /// \brief  �R���X�g���N�^
    ///
    /// \param[in] Width         : ���C���[����
    /// \param[in] Height        : ���C���[�c��
    /// \param[in] SampleCount   : 1�s�N�Z��������̃T���v����
    /// \param[in] SampleQuality : �}���`�T���v���̉掿���x��
    /// \param[in] Format        : �e�N�X�`���t�H�[�}�b�g
    ///
    Layer(UINT Width, UINT Height, UINT SampleCount=1U, UINT SampleQuality=0U, Format TextureFormat=Format::R32G32B32A32_UINT);

    ///
    /// \brief  �L���ȃ��C���[���ǂ�������
    ///
    ///         true  : �L��
    ///         false : ����
    ///
    /// \return ���茋��
    ///
    bool isValid() const noexcept { return Texture::isValid() && layer_; }
    operator bool() const noexcept { return isValid(); }


    ///< ���C���[���擾
    ID3D11RenderTargetView* layer() const noexcept { layer_.Get(); }
protected :
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> layer_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_LAYER_HEADER_
// EOF
