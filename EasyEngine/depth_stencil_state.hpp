///
/// \file   depth_stencil_state.hpp
/// \brief  �[�x�X�e���V����Ԓ�`�N���X��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/9/4
///             - �w�b�_�ǉ�
///
#ifndef INCLUDED_EGEG_GLIB_DEPTH_STENCIL_STATE_HEADER_
#define INCLUDED_EGEG_GLIB_DEPTH_STENCIL_STATE_HEADER_

#include <cstdint>
#include <d3d11.h>
#include <wrl.h>

namespace easy_engine {
namespace g_lib {

/******************************************************************************

    DepthStencilDesc

******************************************************************************/
/// �[�x�X�e���V���e�X�g���Ɏ��s����X�e���V������
// �ڍ� : https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_stencil_op
enum class StencilOperation {
    kKeep,
    kZero,
    kReplace,
    kIncrementSat,
    kDecrementSat,
    kInvert,
    kIncrement,
    kDecrement
};

/// �[�x�f�[�^�Ɗ����̐[�x�f�[�^�̔�r�I�v�V����
// �ڍ� : https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_comparison_func
enum class DepthStencilComparison {
    kNever,
    kLess,
    kEqual,
    kLessEqual,
    kGreater,
    kNotEqual,
    kGreaterEqual,
    kAlways
};

/// �X�e���V���e�X�g�̌��ʂɊ�Â��Ď��s����X�e���V������
struct StencilOperationDesc {
    StencilOperation fail;       ///< �X�e���V���e�X�g�����s�����ꍇ�Ɏ��s���鑀��
    StencilOperation depth_fail; ///< �X�e���V���e�X�g��ʉ߁A�[�x�e�X�g�Ɏ��s�����ꍇ�Ɏ��s���鑀��
    StencilOperation pass;       ///< �X�e���V���e�X�g�A�[�x�e�X�g�̗�����ʉ߂����ꍇ�Ɏ��s���鑀��
    DepthStencilComparison func; ///< �e�X�g���ʂƊ��ɂ���f�[�^�Ƃ̔�r����
};

struct DepthStencilDesc {
    bool depth_enable;                 ///< �[�x�e�X�g�̗L���@true:�L���@false:����
    bool depth_write_enable;           ///< �[�x�l�������݂̗L���@true:�L���@false:����
    DepthStencilComparison depth_func; ///< �[�x�e�X�g���ʂƊ��ɂ���f�[�^�Ƃ̔�r����
    bool stencil_enable;               ///< �X�e���V���e�X�g�̗L���@true:�L���@false:����
    std::uint8_t stencil_read_mask;    ///< �X�e���V���f�[�^��ǂݍ��ނ��߂̃}�X�N
    std::uint8_t stencil_write_mask;   ///< �X�e���V���f�[�^���������ނ��߂̃}�X�N
    StencilOperationDesc front_face;   ///< �\�ʖ@�����J�����̕����������Ă���s�N�Z���́A�e�X�g���ʂ̎g�p���@
    StencilOperationDesc back_face;    ///< �\�ʖ@�����J�������痣�ꂽ�����������Ă���s�N�Z���́A�e�X�g���ʂ̎g�p���@
};


/******************************************************************************

    DepthStencilState

******************************************************************************/
///
/// \brief  �[�x�X�e���V����Ԓ�`�N���X
///
class DepthStencilState {
public :
    ///
    /// \brief  �f�t�H���g�̃R���X�g���N�^
    ///
    ///         ��Ԃ̒�`�������܂���B
    ///
    DepthStencilState() = default;

    ///
    /// \brief  �[�x�X�e���V���X�e�[�g�̍쐬�𔺂��R���X�g���N�^
    ///
    /// \param[in] Desc : �[�x�X�e���V���̏�Ԓ�`�\����
    ///
    DepthStencilState(const DepthStencilDesc& Desc);

    ///
    /// \brief  �L���Ȑ[�x�X�e���V����Ԓ�`�I�u�W�F�N�g���ǂ�������
    ///
    ///         true  : �L��
    ///         false : ����
    ///
    /// \return ���茋��
    ///
    bool isValid() const noexcept { return state_; }
    operator bool() const noexcept { return isValid(); }

    /// �[�x�X�e���V���X�e�[�g�I�u�W�F�N�g���擾
    ID3D11DepthStencilState* state() const noexcept { state_.Get(); }
private :
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> state_;
};


/******************************************************************************

    depth-stencil presets

******************************************************************************/
// �Q�l : https://github.com/microsoft/DirectXTK
//        https://github.com/microsoft/DirectXTK/blob/master/Src/CommonStates.cpp
  namespace depth_stencil_impl {
      inline DepthStencilState createDS(const bool E, const bool W) {
          return DepthStencilState {
              DepthStencilDesc {
                E,
                W, DepthStencilComparison::kLessEqual,
                false, D3D11_DEFAULT_STENCIL_READ_MASK, D3D11_DEFAULT_STENCIL_WRITE_MASK,
                StencilOperationDesc {StencilOperation::kKeep, StencilOperation::kKeep, StencilOperation::kKeep, DepthStencilComparison::kAlways},
                StencilOperationDesc {StencilOperation::kKeep, StencilOperation::kKeep, StencilOperation::kKeep, DepthStencilComparison::kAlways}
              }
          };
      }
  } // namespace depth_stencil_impl

namespace depth_stencil_preset {
/// �[�x�e�X�g�A�X�e���V���e�X�g����
inline DepthStencilState none() { return depth_stencil_impl::createDS(false, false); }
/// �[�x�e�X�g����A�X�e���V���e�X�g�����B�[�x�l�������݂Ȃ�
inline DepthStencilState read() { return depth_stencil_impl::createDS(true, false); }
/// �[�x�e�X�g����A�X�e���V���e�X�g�����B�[�x�l�������݂���
inline DepthStencilState write() { return depth_stencil_impl::createDS(true, true); }
} // namespace depth_stencil_preset

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_DEPTH_STENCIL_STATE_HEADER_
// EOF
