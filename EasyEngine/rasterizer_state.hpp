///
/// \file   rasterizer_state.hpp
/// \brief  ���X�^���C�U��Ԓ�`�N���X��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/9/8
///             - �w�b�_�ǉ�
///             - RasterizerState ��`
///             - RasterizerDesc ��`
///                 -
///
#ifndef INCLUDED_EGEG_GLIB_RASTERIZER_STATE_HEADER_
#define INCLUDED_EGEG_GLIB_RASTERIZER_STATE_HEADER_

#include <d3d11.h>
#include <wrl.h>

namespace easy_engine {
namespace g_lib {

/******************************************************************************

    RasterizerDesc

******************************************************************************/
/// 3�p�`�������_�����O����Ƃ��̓h��Ԃ����@
// �ڍ� : https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_rasterizer_desc
enum class RasterizerFillMode {
    kWireframe,
    kSolid
};

/// �`�悵�Ȃ�3�p�`�̕���
// �ڍ� : https://docs.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_rasterizer_desc
enum class RasterizerCullMode {
    kNone,
    kFront,
    kBack
};

/// ���ʂƂ��Ĉ���3�p�`�̒��_�̕���
enum class RasterizerFront {
    kCounterClockWise, ///< �����v���肪����
    kClockWise         ///< ���v��肪����
};

struct RasterizerDesc {
    RasterizerFillMode fill_mode;   ///< 3�p�`�̓h��Ԃ����@
    RasterizerCullMode cull_mode;   ///< �`�悵�Ȃ�3�p�`�̎w��
    RasterizerFront front;          ///< ���ʂƂ��Ĉ���3�p�`
    int depth_bias;                 ///< �s�N�Z���ɒǉ������[�x�l
    float depth_bias_clamp;         ///< �ő�[�x�o�C�A�X
    float slope_scaled_depth_bias;  ///< �s�N�Z���̌X��
    bool depth_clip_enable;         ///< �����ɖ߂Â����N���b�s���O��L���ɂ��邩�@true:�L���@false:����
    bool scissor_enable;            ///< �V�U�[��`�������O��L���ɂ��邩�@true:�L���@false:����
    bool multisample_enable;        ///< �}���`�T���v����L���ɂ��邩�@true:�L���@false:����
    bool antialiased_line_enable;   ///< ���̕`��ɃA���`�G�C���A�X���g�p���邩(multisample_enable��false�̂Ƃ��̂�)�@true:�L���@false:����
};


/******************************************************************************

    RasterizerState

******************************************************************************/
///
/// \brief  ���X�^���C�U��Ԓ�`�N���X
///         
class RasterizerState {
public :
    ///
    /// \brief  �f�t�H���g�̃R���X�g���N�^
    ///
    ///         ��Ԃ̒�`�������܂���B
    ///
    RasterizerState() = default;

    ///
    /// \brief  ���X�^���C�U�X�e�[�g�̍쐬�𔺂��R���X�g���N�^
    ///
    /// \param[in] Desc : ���X�^���C�U�X�e�[�g�̏�Ԓ�`�\����
    ///
    RasterizerState(const RasterizerDesc& Desc);

    ///
    /// \brief  �L���ȃ��X�^���C�U��Ԓ�`�I�u�W�F�N�g���ǂ�������
    ///
    ///         true  : �L��
    ///         false : ����
    ///
    bool isValid() const noexcept { return state_; }
    operator bool() const noexcept { return isValid(); }


    /// ���X�^���C�U�X�e�[�g�I�u�W�F�N�g���擾
    ID3D11RasterizerState* state() const noexcept { state_.Get(); }
private :
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> state_;
};


/******************************************************************************

    rasterizer presets

******************************************************************************/
// �Q�l : https://github.com/microsoft/DirectXTK
//        https://github.com/microsoft/DirectXTK/blob/master/Src/CommonStates.cpp
  namespace rasterizer_impl {
      inline RasterizerState createRS(const RasterizerFillMode F, const RasterizerCullMode C) {
          return RasterizerState {
              RasterizerDesc {
                F,
                C,
                RasterizerFront{},
                0, 0.0F, 0.0F,
                true,
                false,
                true,
                false
              }
          };
      }
  } // namespace rasterizer_impl

namespace rasterizer_preset {
/// fill:kSolid�@cull:kNone
inline RasterizerState cullNone() { return rasterizer_impl::createRS(RasterizerFillMode::kSolid, RasterizerCullMode::kNone); }
// fill:kSolid�@cull:kBack
inline RasterizerState solid() { return rasterizer_impl::createRS(RasterizerFillMode::kSolid, RasterizerCullMode::kBack); }
// fill:kWireframe cull:kBack
inline RasterizerState wireframe() { return rasterizer_impl::createRS(RasterizerFillMode::kWireframe, RasterizerCullMode::kBack); }
// fill:kWireframe cull:kNone
inline RasterizerState nonCullingwireframe() { return rasterizer_impl::createRS(RasterizerFillMode::kWireframe, RasterizerCullMode::kNone); }
} // namespace rasterizer_preset

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_RASTERIZER_STATE_HEADER_
// EOF
