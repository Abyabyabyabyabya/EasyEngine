///
/// \file   blend_state.hpp
/// \brief  �u�����h��Ԓ�`�N���X��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/9/4
///             - �w�b�_�ǉ�
///             - BlendState ��`
///             - BlendDesc ��`
///                 - BlendCoefficient ��`
///                 - BlendOperation ��`
///                 - OpaqueBlend ��`
///                 - AlphaBlend ��`
///                 - AddtiveBlend ��`
///                 - NonPremultipliedBlend ��`
///         - 2020/9/8
///             - �v���Z�b�g���֐��ɒu��������
///
#ifndef INCLUDED_EGEG_GLIB_BLEND_STATE_HEADER_
#define INCLUDED_EGEG_GLIB_BLEND_STATE_HEADER_

#include <array>
#include <d3d11.h>
#include <wrl.h>
#include "color.hpp"

namespace easy_engine {
namespace g_lib {

/******************************************************************************

    BlendDesc

******************************************************************************/
/// ���͂ɑ΂���W��
// �ڍ� : https://docs.microsoft.com/en-us/windows/win32/api/D3D11/ne-d3d11-d3d11_blend
enum class BlendCoefficient {
    kZero,
    kOne,
    kSrcColor,
    kInvSrcColor,
    kSrcAlpha,
    kInvSrcAlpha,
    kDestAlpha,
    kInvDestAlpha,
    kDestColor,
    kInvDestColor,
    kSrcAlphaSat,
    kBlendFactor,
    kInvBlendFactor,
    kSrc1Color,
    kInvSrc1Color,
    kSrc1Alpha,
    kInvSrc1Alpha	
};
/// �u�����h���Z
// �ڍ� : https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_blend_op
enum class BlendOperation {
    kAdd,
    kSubtract,
    kRevSubtract,
    kMin,
    kMax
};

struct BlendDesc {
    bool enable;                      ///< true:�u�����h����@false : �u�����h�Ȃ�
    BlendCoefficient src_coef;        ///< �\�[�X�F�ɑ΂���W��
    BlendCoefficient dest_coef;       ///< �������ݐ�̐F�ɑ΂���W��
    BlendOperation operation;         ///< �u�����h���Z
    BlendCoefficient src_alpha_coef;  ///< �\�[�X���l�ɑ΂���W��
    BlendCoefficient dest_alpha_coef; ///< �������ݐ惿�l�ɑ΂���W��
    BlendOperation alpha_operation;   ///< ���u�����h���Z
    ColorFlag write_color_mask;       ///< �������ސF(�r�b�g�t���O)
};


/******************************************************************************

    BlendState

******************************************************************************/
///
/// \brief  �u�����h��Ԓ�`�N���X
///
class BlendState {
public :
    ///
    /// \brief  �f�t�H���g�̃R���X�g���N�^
    ///
    ///         ��Ԃ̒�`�������܂���B
    ///
    BlendState() = default;

    ///
    /// \brief  �u�����h�X�e�[�g�̍쐬�𔺂��R���X�g���N�^
    ///
    ///         ��2�����ɂ͏o�̓^�[�Q�b�g���̃u�����h��Ԃ�ݒ�ł��܂��B
    ///         �����̃^�[�Q�b�g��ݒ肷��ꍇ��std::array<�c>�Ɋi�[���ēn���Ă��������B
    ///
    /// \param[in] Desc : �u�����h��Ԓ�`�\����
    /// \param[in] AlphaToCaverageEnable : �A���t�@�g�D�J���@���b�W�w��t���O�@true:�L���@false:����
    ///
    /// \attention �����̃^�[�Q�b�g��ݒ肷��ہA�ݒ�ł���ő吔��8�ł��B
    ///
    BlendState(const BlendDesc& Desc, bool AlphaToCaverageEnable=false);
    BlendState(const std::array<BlendDesc, 8U>& Descs, bool AlphaToCaverageEnable=false);

    ///
    /// \brief  �L���ȃu�����h��Ԓ�`�I�u�W�F�N�g���ǂ�������
    ///
    ///         true  : �L��
    ///         false : ����
    ///
    /// \return ���茋��
    ///
    bool isValid() const noexcept { return state_; }
    operator bool() const noexcept { return isValid(); }


    /// �u�����h�X�e�[�g�I�u�W�F�N�g���擾
    ID3D11BlendState* state() const noexcept { return state_.Get(); }
private :
    Microsoft::WRL::ComPtr<ID3D11BlendState> state_;
};


/******************************************************************************

    blend presets

******************************************************************************/
// �Q�l : https://github.com/microsoft/DirectXTK
//        https://github.com/microsoft/DirectXTK/blob/master/Src/CommonStates.cpp
  namespace blend_impl {
      inline BlendState createBlend(const bool E, const BlendCoefficient Src, const BlendCoefficient Dest, const BlendOperation Op) {
          return BlendState {
              BlendDesc {
                E,
                Src, Dest, Op,
                Src, Dest, Op,
                kColorBitMask<1,1,1,1>
              }
          };
      }
  }

namespace blend_presets {
/// �u�����h����
inline BlendState opaque() { return blend_impl::createBlend(false, BlendCoefficient::kOne, BlendCoefficient::kZero, BlendOperation::kAdd); }
/// ���u�����h
inline BlendState alpha() { return blend_impl::createBlend(true, BlendCoefficient::kOne, BlendCoefficient::kInvSrcAlpha, BlendOperation::kAdd); }
/// ���Z����
inline BlendState addtive() { return blend_impl::createBlend(true, BlendCoefficient::kSrcAlpha, BlendCoefficient::kOne, BlendOperation::kAdd); }
/// ���O��Z����
inline BlendState nonPremultiplied() { return blend_impl::createBlend(true, BlendCoefficient::kSrcAlpha, BlendCoefficient::kInvSrcAlpha, BlendOperation::kAdd); }
} // namespace blend_preset

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_BLEND_STATE_HEADER_
// EOF
