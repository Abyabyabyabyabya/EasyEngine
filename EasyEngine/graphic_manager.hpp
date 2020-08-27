///
/// \fiel   graphic_manager.hpp
/// \brief  �O���t�B�b�N�}�l�[�W���[��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/8/21
///             - �w�b�_�ǉ�
///             - GraphicManager ��`
///
#ifndef INCLUDED_EGEG_GLIB_GRAPHIC_MANAGER_HEADER_
#define INCLUDED_EGEG_GLIB_GRAPHIC_MANAGER_HEADER_

#include <memory>
#include <d3d11.h>
#include <wrl.h>
#include "noncopyable.hpp"
#include "layer.hpp"
#include "update_manager.hpp"

namespace easy_engine {
class EasyEngine;
   
namespace g_lib {

///
/// \class  GraphicManager
/// \brief  �`��}�l�[�W���[
///
///         ���̃N���X�ւ̃A�N�Z�X�́AEasyEngine::graphics()���g�p���Ă��������B
///
class GraphicManager final : t_lib::Noncopyable<GraphicManager> {
public :
    friend EasyEngine;

    ~GraphicManager();

    void capture(const char* FileName, const Texture& Image);
    Layer baseLayer() const noexcept { return base_layer_; }

    ///
    /// \brief  �g�p���Ă���D3D�@�\���x�����擾
    ///
    /// \return �@�\���x��
    ///
    D3D_FEATURE_LEVEL d3dFeatureLevel() const noexcept { return feature_level_; }
    
    ///
    /// \brief  D3D�f�o�C�X���擾
    ///
    /// \return D3D�f�o�C�X
    ///
    ID3D11Device& d3d11Device() const noexcept { return *device_.Get(); }

    ///
    /// \brief  D3D�R���e�L�X�g���擾
    ///
    /// \return D3D�R���e�L�X�g
    ///
    ID3D11DeviceContext& d3d11Context() const noexcept { return *context_.Get(); }

private :
    static std::unique_ptr<GraphicManager> create(); // EasyEngine�N���X�ɂ��Ăяo�����֐�
    GraphicManager() = default;
    void render(Time);

    D3D_FEATURE_LEVEL feature_level_;
    Microsoft::WRL::ComPtr<ID3D11Device> device_;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context_;
    Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain_;
    Layer base_layer_;
    typename UpdateManager<EasyEngine>::TaskInfo task_;
};

} // namespace g_lib
} // namespace easy_engine
#endif  // !INCLUDED_EGEG_GLIB_GRAPHIC_MANAGER_HEADER_
// EOF
