///
/// \file   scene_state.hpp
/// \brief  �V�[���X�e�[�g��`�N���X��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/8/31
///             - �w�b�_�ǉ�
///             - SceneState ��`
///
#ifndef INCLUDED_EGEG_GLIB_SCENE_STATE_HEADER_
#define INCLUDED_EGEG_GLIB_SCENE_STATE_HEADER_

#include <d3d11.h>
#include <wrl.h>

namespace easy_engine {
namespace g_lib {

///
/// \class  SceneState
/// \brief  �V�[���X�e�[�g��`�N���X
///
class SceneState {
public :


private :
    Microsoft::WRL::ComPtr<ID3D11BlendState> blend_state_;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizer_state_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_stencil_state_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_SCENE_STATE_HEADER_
// EOF
