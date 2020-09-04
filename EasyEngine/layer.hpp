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

#include "texture_resource.hpp"

namespace easy_engine {
namespace g_lib {

/******************************************************************************

    Layer

******************************************************************************/
///
/// \brief  ���C���[(�V�F�[�_�[���\�[�X & �����_�[�^�[�Q�b�g)
///
class Layer : public TextureResource {
public :
    ///
    /// \enum   Format
    /// \brief  �e�N�X�`���t�H�[�}�b�g
    ///
    ///         �ڍׂ�Microsoft DXGI_FORMAT enumeration���Q�Ƃ��Ă��������B
    ///         https://docs.microsoft.com/en-us/windows/win32/api/dxgiformat/ne-dxgiformat-dxgi_format
    ///
    enum class Format : UINT {
        kUnknown,
        kRGBA32Typeless,
        kRGBA32Float,
        kRGBA32Uint,
        kRGBA32Sint,
        kRGB32Typeless,
        kRGB32Float,
        kRGB32Uint,
        kRGB32Sint,
        kRGBA16Typeless,
        kRGBA16Float,
        kRGBA16Unorm,
        kRGBA16Uint,
        kRGBA16Snorm,
        kRGBA16Sint,
        kRG32Typeless,
        kRG32Float,
        kRG32Uint,
        kRG32Sint,
        kR32G8X24Typeless,
        kR32FloatX8x24Typeless,
        kX32TypelessG8X24Uint,
        kRGB10A2Typeless,
        kRGB10A2Unorm,
        kRGB10A2Uint,
        kRG11B10Float,
        kRGBA8Typeless,
        kRGBA8Unorm,
        kRGBA8UnormSRGB,
        kRGBA8Uint,
        kRGBA8Snorm,
        kRGBA8Sint,
        kRG16Typeless,
        kRG16Float,
        kRG16Unorm,
        kRG16Uint,
        kRG16Snorm,
        kRG16Sint,
        kR32Typeless,
        kR32Float,
        kR32Uint,
        kR32Sint,
        kR24G8Typeless,
        kR24UnormX8Typeless,
        kX24TypelessG8Uint,
        kRG8Typeless,
        kRG8Unorm,
        kRG8Uint,
        kRG8Snorm,
        kRG8Sint,
        kR16Typeless,
        kR16Float,
        kR16Unorm,
        kR16_UINT,
        kR16Snorm,
        kR16Sint,
        kR8Typeless,
        kR8Unorm,
        kR8Uint,
        kR8Snorm,
        kR8Sint,
        kA8Unorm,
        kR1Unorm,
        kRGB9E5SharedExp,
        kRG8BG8Unorm,
        kGR8GB8Unorm,
        kBC1Typeless,
        kBC1Unorm,
        kBC1UnormSRGB,
        kBC2Typeless,
        kBC2Unorm,
        kBC2UnormSRGB,
        kBC3Typeless,
        kBC3Unorm,
        kBC3UnormSRGB,
        kBC4Typeless,
        kBC4Unorm,
        kBC4Snorm,
        kBC5Typeless,
        kBC5Unorm,
        kBC5Snorm,
        kB5G6R5Unorm,
        kBGR5A1Unorm,
        kBGRA8Unorm,
        kBGRX8Unorm,
        kRGB10XRBiasA2Unorm,
        kBGRA8Typeless,
        kBGRA8UnormSRGB,
        kBGRX8Typeless,
        kBGRX8UnormSRGB,
        kBC6HTypeless,
        kBC6HUF16,
        kBC6HSF16,
        kBC7Typeless,
        kBC7Unorm,
        kBC7UnormSRGB,
        kBGRA4Unorm
    };

    Layer() = default;

    ///
    /// \brief  �e�N�X�`���̍쐬�𔺂��R���X�g���N�^
    ///
    /// \param[in] Width         : ���C���[����
    /// \param[in] Height        : ���C���[�c��
    /// \param[in] Format        : �e�N�X�`���t�H�[�}�b�g
    /// \param[in] SampleCount   : 1�s�N�Z��������̃T���v����
    /// \param[in] SampleQuality : �}���`�T���v���̉掿���x��
    ///
    Layer(unsigned Width, unsigned Height, Format TextureFormat=Format::kRGBA8Uint, UINT SampleCount=1U, UINT SampleQuality=0U);

    ///
    /// \brief  �L���ȃ��C���[���ǂ�������
    ///
    ///         true  : �L��
    ///         false : ����
    ///
    /// \return ���茋��
    ///
    bool isValid() const noexcept { return TextureResource::isValid() && texture_ && layer_; }
    operator bool() const noexcept { return isValid(); }


    /// �e�N�X�`�����擾
    ID3D11ShaderResourceView* texture() const noexcept { return texture_.Get(); }
    /// ���C���[���擾
    ID3D11RenderTargetView* layer() const noexcept { return layer_.Get(); }
protected :
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture_;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> layer_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_LAYER_HEADER_
// EOF
