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

#include <d3d11.h>
#include <wrl.h>

namespace easy_engine {
namespace g_lib {

/******************************************************************************

    DepthStencilDesc

******************************************************************************/
enum class StencilOperation {
};

/// �[�x�f�[�^�Ɗ����̐[�x�f�[�^�̔�r�I�v�V����
enum class DepthStencilComparison {

};

struct DepthStencilDesc {

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
    /// \brief  �L���Ȑ[�x�X�e���V����Ԓ�`�N���X���ǂ�������
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

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_DEPTH_STENCIL_STATE_HEADER_
// EOF
