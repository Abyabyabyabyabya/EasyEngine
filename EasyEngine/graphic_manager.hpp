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

#include <vector>
#include <memory>
#include <d3d11.h>
#include <wrl.h>
#include "noncopyable.hpp"
#include "update_manager.hpp"
#include "layer.hpp"
#include "scene_state.hpp"
#include "shader_slot.hpp"
#include "index_buffer.hpp"
#include "vertex_buffer.hpp"
#include "vertex_shader.hpp"
#include "geometry_shader.hpp"
#include "pixel_shader.hpp"
#include "render_mesh.hpp"

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

    TextureResource capture(const TextureResource& Texture);
    void saveTexture(const char* FileName, const TextureResource& Image);
    Layer baseLayer() const noexcept { return base_layer_; }

    void clearLayer(const Layer& Target, const float(&ClearColor)[4]);
    void clearPipeline();

    void setLayer(UINT Slot, const Layer& Target);
    void setLayers(UINT StartSlot, const std::vector<Layer>& Targets);
    void setSceneState(const SceneState& State);
    void setVertexShader(const VertexShader& VS);
    void setVertexShaderSlot(const ShaderSlot& Slot);
    void setGeometryShader(const GeometryShader& GS);
    void setGeometryShaderSlot(const ShaderSlot& Slot);
    void setPixelShader(const PixelShader& PS);
    void setPixelShaderSlot(const ShaderSlot& Slot);

    void draw(const RenderMesh& Mesh, UINT IndexCount, UINT BaseIndexLocation=0, INT BaseVertexLocation=0);
    void drawInstanced(UINT InstanceCount, const RenderMesh& Mesh, UINT IndexCountPerMesh, UINT BaseIndexLocation=0, INT BaseVertexLocation=0, UINT StartInstanceLocation=0);


    ///< �g�p���Ă���D3D�@�\���x�����擾
    D3D_FEATURE_LEVEL d3dFeatureLevel() const noexcept { return feature_level_; }
    ///< D3D�f�o�C�X���擾
    ID3D11Device& d3d11Device() const noexcept { return *device_.Get(); }
    ///< D3D�C�~�f�B�G�C�g�R���e�L�X�g���擾
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
#endif // !INCLUDED_EGEG_GLIB_GRAPHIC_MANAGER_HEADER_
// EOF
