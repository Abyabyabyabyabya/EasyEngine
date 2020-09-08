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
///             - SamplerDesc ��`
///                 - SamplerFilter ��`
///                 - SamplerAddressMode ��`
///                 - SamplerComparison ��`
///                 - PointWrapSampler ��`
///                 - PointMirrorSampler ��`
///                 - PointClampSampler ��`
///                 - PointBorderSampler ��`
///                 - PointMirrorOnceSampler ��`
///                 - LinearWrapSampler ��`
///                 - LinearMirrorSampler ��`
///                 - LinearClampSampler ��`
///                 - LinearBorderSampler ��`
///                 - LinearMirrorOnceSampler ��`
///                 - AnisotropicWrapSampler ��`
///                 - AnisotropicMirrorSampler ��`
///                 - AnisotropicClampSampler ��`
///                 - AnisotropicBorderSampler ��`
///                 - AnisotropicMirrorOnceSampler ��`
///         - 2020/9/8
///             - �v���Z�b�g���֐��ɒu��������
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

/// �T���v�����O���ꂽ�f�[�^�Ɗ����̃T���v�����O�ς݃f�[�^�̔�r����
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
    /// \brief  �L���ȃT���v���[��Ԓ�`�I�u�W�F�N�g���ǂ�������
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


/******************************************************************************

    sampler presets

******************************************************************************/
// �Q�l : https://github.com/microsoft/DirectXTK
//        https://github.com/microsoft/DirectXTK/blob/master/Src/CommonStates.cpp
  namespace sampler_impl { 
      inline SamplerState createSampler(const SamplerFilter F, const SamplerAddressMode A, const Color C=Color{0}) {
          return SamplerState {
              SamplerDesc {
                F,
                A, A, A,
                0.0F,
                D3D11_MAX_MAXANISOTROPY,
                SamplerComparison::kNever,
                Color{0},
                0.0F, D3D11_FLOAT32_MAX
              }
          };
      }
  } // namespace sampler_impl

namespace sampler_presets {
// point
inline SamplerState pointWrap() { return sampler_impl::createSampler(SamplerFilter::kMinMagMipPoint, SamplerAddressMode::kWrap); }
inline SamplerState pointMirror() { return sampler_impl::createSampler(SamplerFilter::kMinMagMipPoint, SamplerAddressMode::kMirror); }
inline SamplerState pointClamp() { return sampler_impl::createSampler(SamplerFilter::kMinMagMipPoint, SamplerAddressMode::kClamp); }
inline SamplerState pointBorder(const Color BorderColor) { return sampler_impl::createSampler(SamplerFilter::kMinMagMipPoint, SamplerAddressMode::kBorder, BorderColor); }
inline SamplerState pointMirrorOnce() { return sampler_impl::createSampler(SamplerFilter::kMinMagMipPoint, SamplerAddressMode::kMirrorOnce); }
// linear
inline SamplerState linearWrap() { return sampler_impl::createSampler(SamplerFilter::kMinMagMipLinear, SamplerAddressMode::kWrap); }
inline SamplerState linearMirror() { return sampler_impl::createSampler(SamplerFilter::kMinMagMipLinear, SamplerAddressMode::kMirror); }
inline SamplerState linearClamp() { return sampler_impl::createSampler(SamplerFilter::kMinMagMipLinear, SamplerAddressMode::kClamp); }
inline SamplerState linearBorder(const Color BorderColor) { return sampler_impl::createSampler(SamplerFilter::kMinMagMipLinear, SamplerAddressMode::kBorder, BorderColor);}
inline SamplerState linearMirrorOnce() { return sampler_impl::createSampler(SamplerFilter::kMinMagMipLinear, SamplerAddressMode::kMirrorOnce); }
// anisotropic
inline SamplerState anisotropicWrap() { return sampler_impl::createSampler(SamplerFilter::kAnisotropic, SamplerAddressMode::kWrap); }
inline SamplerState anisotropicMirror() { return sampler_impl::createSampler(SamplerFilter::kAnisotropic, SamplerAddressMode::kMirror); }
inline SamplerState anisotropicClamp() { return sampler_impl::createSampler(SamplerFilter::kAnisotropic, SamplerAddressMode::kClamp); }
inline SamplerState anisotropicBorder(const Color BorderColor) { return sampler_impl::createSampler(SamplerFilter::kAnisotropic, SamplerAddressMode::kBorder, BorderColor); }
inline SamplerState anisotropicMirrorOnce() { return sampler_impl::createSampler(SamplerFilter::kAnisotropic, SamplerAddressMode::kMirrorOnce); }
} // namespace sampler_presets

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_SAMPLER_STATE_HEADER_
// EOF
