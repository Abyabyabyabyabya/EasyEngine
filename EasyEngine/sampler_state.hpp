///
/// \file   sampler_state.hpp
/// \brief  �T���v���[��Ԓ�`�N���X��`�w�b�_
///
/// \aurhor ��
///
/// \par    ����
///         - 2020/9/4
///             - �w�b�_�ǉ�
///             - SamplerState ��`
///
#ifndef INCLUDED_EGEG_GLIB_SAMPLER_STATE_HEADER_
#define INCLUDED_EGEG_GLIB_SAMPLER_STATE_HEADER_

#include <cstdint>
#include <d3d11.h>
#include <wrl.h>
#include "color.hpp"

namespace easy_engine {
namespace g_lib {

/******************************************************************************

    SamplerDesc

******************************************************************************/
/// �t�B���^�����O���@
// �ڍ� : https://docs.microsoft.com/en-us/windows/win32/api/D3D11/ne-d3d11-d3d11_filter
enum class SamplerFilter {
    kMinMagMipPoint,
    kMinMagPointMipLinear,
    kMinPointMagLinearMipPoint,
    kMinPointMagMipLinear,
    kMinLinearMagMipPoint,
    kMinLinearMagPointMipLinear,
    kMinMagLinearMipPoint,
    kMinMagMipLinear,
    kAnisotropic,

    kComparisonMinMagMipPoint,
    kComparisonMinMagPointMipLinear,
    kComparisonMinPointMagLinearMipPoint,
    kComparisonMinPointMagMipLinear,
    kComparisonMinLinearMagMipPoint,
    kComparisoninLinearMagPointMipLinear,
    kComparisoninMagLinearMipPoint,
    kComparisoninMagMipLinear,
    kComparisonAnisotropic,

    kMinimumMinMagMipPoint,
    kMinimumMinMagPointMipLinear,
    kMinimumMinPointMagLinearMipPoint,
    kMinimumMinPointMagMipLinear,
    kMinimumMinLinearMagMipPoint,
    kMinimuminLinearMagPointMipLinear,
    kMinimuminMagLinearMipPoint,
    kMinimuminMagMipLinear,
    kMinimumAnisotropic,

    kMaximumMinMagMipPoint,
    kMaximumMinMagPointMipLinear,
    kMaximumMinPointMagLinearMipPoint,
    kMaximumMinPointMagMipLinear,
    kMaximumMinLinearMagMipPoint,
    kMaximuminLinearMagPointMipLinear,
    kMaximuminMagLinearMipPoint,
    kMaximuminMagMipLinear,
    kMaximumAnisotropic
};

/// �e�N�X�`���͈̔͊O�ɂȂ�uv���W�̉������@
// �ڍ� : https://docs.microsoft.com/en-us/windows/win32/api/D3D11/ne-d3d11-d3d11_texture_address_mode
enum class SamplerAddressMode {
    kWrap,
    kMirror,
    kClamp,
    kBorder,
    kMirrorOnce
};

/// �T���v�����O���ꂽ�f�[�^�Ɗ����̃T���v�����O�ς݃f�[�^�̔�r�I�v�V����
// �ڍ� : https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_comparison_func
enum class SamplerComparison {
    kNever,
    kLess,
    kEqual,
    kLessEqual,
    kGreater,
    kNotEqual,
    kGreaterEqual,
    kAlways
};

struct SamplerDesc {
    SamplerFilter filter;         ///< �e�N�X�`�����T���v�����O����ۂ̃t�B���^�����O���@
    SamplerAddressMode address_u; ///< �͈͊O�̃e�N�X�`��u���W�̉������@
    SamplerAddressMode address_v; ///< �͈͊O�̃e�N�X�`��v���W�̉������@
    SamplerAddressMode address_w; ///< �͈͊O�̃e�N�X�`��w���W�̉������@
    float mip_lod_bias;           ///< �v�Z���ꂽ�݂��Ճ}�b�v���x������̃I�t�Z�b�g
    unsigned max_anisotropy;      ///< filter��kAnisotropic��kComparisonAnisotropic���w�肵���ꍇ�Ɏg�p�����N�����v�l(1~16)
    SamplerComparison comparison; ///< �T���v�����O�ς݃f�[�^��r�I�v�V����
    Color border_color;           ///< address_�Z��kBorder���w�肵���ꍇ�Ɏg�p���鋫�E���̐F
    float min_lod;                ///< �A�N�Z�X���N�����v����~�b�v�}�b�v�̉����l
    float max_lod;                ///< �A�N�Z�X���N�����v����~�b�v�}�b�v�̏���l
};

/******************************************************************************

    Sampler Presets

******************************************************************************/
// �Q�l : https://github.com/microsoft/DirectXTK
//        https://github.com/microsoft/DirectXTK/blob/master/Src/CommonStates.cpp

  namespace sampler_impl {
    struct SamplerPresetCommon : SamplerDesc {
        SamplerPresetCommon(
          const SamplerFilter Filter, const SamplerAddressMode AddressMode, const Color BorderColor=Color{0}) : 
            SamplerDesc {
              Filter,
              AddressMode,
              AddressMode,
              AddressMode,
              0.0F,
              D3D11_MAX_MAXANISOTROPY,
              SamplerComparison::kNever,
              Color{0},
              0.0F,
              D3D11_FLOAT32_MAX} {}
    };
  } // namespace sampler_impl

// �|�C���g���b�v
struct PointWrapSampler : sampler_impl::SamplerPresetCommon {
    PointWrapSampler() : SamplerPresetCommon {SamplerFilter::kMinMagMipPoint, SamplerAddressMode::kWrap} {}
};
// �|�C���g�~���[
struct PointMirrorSampler : sampler_impl::SamplerPresetCommon {
    PointMirrorSampler() : SamplerPresetCommon {SamplerFilter::kMinMagMipPoint, SamplerAddressMode::kMirror} {}
};
// �|�C���g�N�����v
struct PointClampSampler : sampler_impl::SamplerPresetCommon {
    PointClampSampler() : SamplerPresetCommon {SamplerFilter::kMinMagMipPoint, SamplerAddressMode::kClamp} {}
};
// �|�C���g�{�[�_�[
struct PointBorderSampler : sampler_impl::SamplerPresetCommon {
    PointBorderSampler(const Color BorderColor=kWhite) : 
      SamplerPresetCommon {SamplerFilter::kMinMagMipPoint, SamplerAddressMode::kBorder, BorderColor} {}
};
// �|�C���g�~���[�����X
struct PointMirrorOnceSampler : sampler_impl::SamplerPresetCommon {
    PointMirrorOnceSampler() : SamplerPresetCommon{SamplerFilter::kMinMagMipPoint, SamplerAddressMode::kMirrorOnce} {}
};

// ���j�A���b�v
struct LinearWrapSampler : sampler_impl::SamplerPresetCommon {
    LinearWrapSampler() : SamplerPresetCommon {SamplerFilter::kMinMagMipLinear, SamplerAddressMode::kWrap} {}
};
// ���j�A�~���[
struct LinearMirrorSampler : sampler_impl::SamplerPresetCommon {
    LinearMirrorSampler() : SamplerPresetCommon {SamplerFilter::kMinMagMipLinear, SamplerAddressMode::kMirror} {}
};
// ���j�A�N�����v
struct LinearClampSampler : sampler_impl::SamplerPresetCommon {
    LinearClampSampler() : SamplerPresetCommon {SamplerFilter::kMinMagMipLinear, SamplerAddressMode::kClamp} {}
};
// ���j�A�{�[�_�[
struct LinearBorderSampler : sampler_impl::SamplerPresetCommon {
    LinearBorderSampler(const Color BorderColor=kWhite) :
      SamplerPresetCommon {SamplerFilter::kMinMagMipLinear, SamplerAddressMode::kBorder, BorderColor} {}
};
// ���j�A�~���[�����X
struct LinearMirrorOnceSampler : sampler_impl::SamplerPresetCommon {
    LinearMirrorOnceSampler() : SamplerPresetCommon{SamplerFilter::kMinMagMipLinear, SamplerAddressMode::kMirrorOnce}{}
};

// �A�j�\�g���s�b�N���b�v
struct AnisotropicWrapSampler : sampler_impl::SamplerPresetCommon {
    AnisotropicWrapSampler() : SamplerPresetCommon {SamplerFilter::kAnisotropic, SamplerAddressMode::kWrap} {}
};
// �A�j�\�g���s�b�N�~���[
struct AnisotropicMirrorSampler : sampler_impl::SamplerPresetCommon {
    AnisotropicMirrorSampler() : SamplerPresetCommon {SamplerFilter::kAnisotropic, SamplerAddressMode::kMirror} {}
};
// �A�j�\�g���s�b�N�N�����v
struct AnisotropicClampSampler : sampler_impl::SamplerPresetCommon {
    AnisotropicClampSampler() : SamplerPresetCommon {SamplerFilter::kAnisotropic, SamplerAddressMode::kClamp} {}
};
// �A�j�\�g���s�b�N�{�[�_�[
struct AnisotropicBorderSampler : sampler_impl::SamplerPresetCommon {
    AnisotropicBorderSampler(const Color BorderColor=kWhite) :
      SamplerPresetCommon {SamplerFilter::kAnisotropic, SamplerAddressMode::kBorder, BorderColor} {}
};
// �A�j�\�g���s�b�N�~���[�����X
struct AnisotropicMirrorOnceSampler : sampler_impl::SamplerPresetCommon {
    AnisotropicMirrorOnceSampler() : SamplerPresetCommon{SamplerFilter::kAnisotropic,SamplerAddressMode::kMirrorOnce}{}
};

using DefaultSampler = LinearClampSampler; ///< �f�t�H���g�̃T���v���[


/******************************************************************************

    SamplerState

******************************************************************************/
///
/// \brief  �T���v���[��Ԓ�`�N���X
///
class SamplerState {
public :
    ///
    /// \brief  �f�t�H���g�̃R���X�g���N�^
    ///
    ///         ��Ԃ̒�`�������܂���B�B
    ///
    SamplerState() = default;

    ///
    /// \brief  �T���v���[�X�e�[�g�̍쐬�𔺂��R���X�g���N�^
    ///
    /// \param[in] Desc : �T���v���[��Ԓ�`�\����
    ///
    SamplerState(const SamplerDesc& Desc);

    ///
    /// \brief  �L���ȃT���v���[��Ԓ�`�N���X���ǂ�������
    ///
    ///         true  : �L��
    ///         false : ����
    ///
    /// \return ���茋��
    ///
    bool isValid() const noexcept { return state_.Get(); }
    operator bool() const noexcept { return isValid(); }


    /// �T���v���[�X�e�[�g�I�u�W�F�N�g���擾
    ID3D11SamplerState* state() const noexcept { return state_.Get(); }
private :
    Microsoft::WRL::ComPtr<ID3D11SamplerState> state_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_SAMPLER_STATE_HEADER_
// EOF
