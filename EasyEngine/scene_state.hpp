///
/// \file   scene_state.hpp
/// \brief  シーンステートオブジェクト定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/31
///             - ヘッダ追加
///             - SceneState 定義
///
#ifndef INCLUDED_EGEG_GLIB_SCENE_STATE_HEADER_
#define INCLUDED_EGEG_GLIB_SCENE_STATE_HEADER_

#include <d3d11.h>
#include <wrl.h>

namespace easy_engine {
namespace g_lib {

///
/// \class  SceneState
/// \brief  シーンステート定義クラス
///
class SceneState {
public :


private :
    Microsoft::WRL::ComPtr<ID3D11BlendState> blend_state_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depth_stencil_state_;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizer_state_;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler_state_;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_stencil_view_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_SCENE_STATE_HEADER_
// EOF
