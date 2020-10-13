///
/// \file   draw_context.hpp
/// \brief  �`��R���e�L�X�g��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/9/10
///             - �w�b�_�ǉ�
///
#ifndef INCLUDED_EGEG_GLIB_DRAW_CONTEXT_HEADER
#define INCLUDED_EGEG_GLIB_DRAW_CONTEXT_HEADER

#include <d3d11.h>
#include <wrl.h>
#include "layer.hpp"
#include "depth_stencil_texture.hpp"
#include "depth_stencil_state.hpp"
#include "blend_state.hpp"
#include "rasterizer_state.hpp"
#include "sampler_state.hpp"
#include "shader_slot.hpp"
#include "index_buffer.hpp"
#include "vertex_buffer.hpp"
#include "vertex_shader.hpp"
#include "geometry_shader.hpp"
#include "pixel_shader.hpp"
#include "render_mesh.hpp"

namespace easy_engine {
namespace g_lib {

class DrawContext {
public :
    DrawContext();

    ///
    /// \brief  �e�N�X�`�����L���v�`��
    ///
    ///         �����̃e�N�X�`�����L���v�`�����ĕԋp
    ///         �߂�l�̃e�N�X�`���͉摜�t�@�C���Ƃ��ĕۑ����邱�Ƃ��\
    ///
    /// \param[in] Texture : �L���v�`������e�N�X�`��
    ///
    /// \return �L���v�`���ς݃e�N�X�`��
    ///
    TextureResource capture(const TextureResource& Texture);
    
    ///
    /// \brief  �R���e�L�X�g���N���A
    ///
    void clear();
    ///
    /// \brief  ���C���[���N���A(�h��Ԃ�)
    ///
    /// \param[in] Target : �N���A���郌�C���[
    /// \param[in] ClearColor : �h��Ԃ��F
    ///
    void clearLayer(const Layer& Target, const float(&ClearColor)[4]);

    ///
    /// \brief  �`��ΏۂƂȂ郌�C���[���Z�b�g
    ///
    /// \param[in] Target       : �Z�b�g���郌�C���[
    /// \param[in] DepthStencil : �[�x�e�N�X�`��
    ///
    void setLayer(const Layer& Target, const DepthStencilTexture& DepthStencil=DepthStencilTexture{});
    ///
    /// \brief  �`��ΏۂƂȂ郌�C���[����x�ɕ����Z�b�g
    ///
    /// \param[in] Targets   : �Z�b�g���郌�C���[���X�g
    /// \param[in] DepthStencil : �[�x�e�N�X�`��
    ///
    void setLayer(const std::vector<Layer>& Targets, const DepthStencilTexture& DepthStencil=DepthStencilTexture{});

    ///
    /// \brief  �u�����h�̏�Ԃ��Z�b�g
    ///
    /// \param[in] BS          : �u�����h�̏�Ԓ�`�I�u�W�F�N�g
    /// \param[in] BlendFactor : �u�����h���萔
    /// \param[in] SampleMask  : �}���`�T���v���`��^�[�Q�b�g�ɂ����ẮA�T���v���p�}�X�N
    ///
    /// BlendFactor�̓u�����h�X�e�[�g�̃u�����h�W���ɁAkBlendFactor��kInvBlendFactor���I������Ă���Ƃ��̂ݗL��
    //  
    ///
    void setBlendState(const BlendState& BS, const float(&BlendFactor)[4], UINT SampleMask=kMaskRGBA);
    ///
    /// \brief  �[�x�X�e���V���̏�Ԃ��Z�b�g
    ///
    /// \param[in] DS         : �[�x�X�e���V���̏�Ԓ�`�I�u�W�F�N�g
    /// \param[in] StencilRef : �X�e���V���e�X�g�Ŏg�p����Q�ƒl
    ///
    void setDepthStencilState(const DepthStencilState& DS, UINT StencilRef=0);
    ///
    ///
    /// \brief  ���X�^���C�U�̏�Ԃ��Z�b�g
    ///
    /// \param[in] RS : ���X�^���C�U�̏�Ԓ�`�I�u�W�F�N�g
    ///
    void setRasterizerState(const RasterizerState& RS);

    ///
    /// \brief  ���_�V�F�[�_�\���Z�b�g
    ///
    /// \param[in] VS : ���_�V�F�[�_�\
    ///
    void setVertexShader(const VertexShader& VS);
    ///
    /// \brief  ���_�V�F�[�_�\�̃V�F�[�_�[�X���b�g���Z�b�g
    ///
    /// \param[in] Slot : �X���b�g
    ///
    void setVertexShaderSlot(const ShaderSlot& Slot);
    ///
    /// \brief  �W�I���g���V�F�[�_�\���Z�b�g
    ///
    /// \param[in] GS : �W�I���g���V�F�[�_�\
    ///
    void setGeometryShader(const GeometryShader& GS);
    ///
    /// \brief  �W�I���g���V�F�[�_�[�̃V�F�[�_�[�X���b�g���Z�b�g
    ///
    /// \param[in] Slot : �X���b�g
    ///
    void setGeometryShaderSlot(const ShaderSlot& Slot);
    ///
    /// \brief  �s�N�Z���V�F�[�_�\���Z�b�g
    ///
    /// \param[in] PS : �s�N�Z���V�F�[�_�\
    ///
    void setPixelShader(const PixelShader& PS);
    ///
    /// \brief  �s�N�Z���V�F�[�_�[�̃V�F�[�_�[�X���b�g���Z�b�g
    ///
    /// \param[in] Slot : �X���b�g
    ///
    void setPixelShaderSlot(const ShaderSlot& Slot);

    ///
    /// \brief  ���b�V����`��
    ///
    /// \param[in] Mesh : �`�悷�郁�b�V��
    /// \param[in] IndexCount : �`�悷�钸�_��
    /// \param[in] BaseIndexLocation : �`����J�n���钸�_�C���f�b�N�X�̊J�n�_
    /// \param[in] BaseVertexLocation : �`����J�n���钸�_�̊J�n�_
    ///
    void draw(const RenderMesh& Mesh, UINT IndexCount, UINT BaseIndexLocation=0, INT BaseVertexLocation=0);
    ///
    /// \brief  ���b�V���̃C���X�^���V���O�`��
    ///
    /// \param[in] InstanceCount : �`�悷��C���X�^���X��
    /// \param[in] Mesh : �`�悷�郁�b�V��
    /// \param[in] IndexCountPerMesh : ���b�V�����̕`�悷�钸�_��
    /// \param[in] BaseIndexLocation : �`����J�n���钸�_�C���f�b�N�X�̊J�n�_
    /// \param[in] BaseVertexLocation : �`����J�n���钸�_�̊J�n�_
    /// \param[in] StartInstanceLocation : �`����J�n����C���X�^���X�̊J�n�_
    ///
    void drawInstanced(UINT InstanceCount, const RenderMesh& Mesh, UINT IndexCountPerMesh, UINT BaseIndexLocation=0, INT BaseVertexLocation=0, UINT StartInstanceLocation=0);
    
    ///
    /// \brief  �R���e�L�X�g���m��
    ///
    ///         ���̊֐����Ăяo������ɁA�R���e�L�X�g�ɕύX�������邱�Ƃ��\�ł��B
    ///         ���̏ꍇ�A�ēxfinish�֐����Ăяo�����܂ŁA�O��̃R���e�L�X�g�͕ێ�����܂��B
    ///
    void finish();

    ///
    /// \brief  �L���ȕ`��R���e�N�X�g���ǂ�������
    ///
    ///         true  : �L��
    ///         false : ����
    ///
    /// \return ���茋��
    ///
    bool isValid() const noexcept { return context_; }
    operator bool() const noexcept { return context_; }


    ///< �f�B�t�@�[�h�R���e�L�X�g���擾
    ID3D11DeviceContext* context() const noexcept { return context_.Get(); }
    ///< �`��R�}���h���X�g���擾
    ID3D11CommandList* commands() const noexcept { return commands_.Get(); }
protected :
    DrawContext(Microsoft::WRL::ComPtr<ID3D11DeviceContext>& Context) noexcept : context_{Context} {}
private :
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context_;
    Microsoft::WRL::ComPtr<ID3D11CommandList> commands_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_DRAW_CONTEXT_HEADER
// EOF
