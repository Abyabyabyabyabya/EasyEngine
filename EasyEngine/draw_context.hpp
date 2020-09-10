///
/// \file   draw_context.hpp
/// \brief  描画コンテキスト定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/9/10
///             - ヘッダ追加
///
#ifndef INCLUDED_EGEG_GLIB_DRAW_CONTEXT_HEADER
#define INCLUDED_EGEG_GLIB_DRAW_CONTEXT_HEADER

#include <d3d11.h>
#include <wrl.h>
#include "layer.hpp"
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
    
    void clearLayer(const Layer& Target, const float(&ClearColor)[4]);
    void clearPipeline();

    void setLayer(UINT Slot, const Layer& Target);
    void setLayers(UINT StartSlot, const std::vector<Layer>& Targets);
    void setDepthStencilState(const DepthStencilState& DS);
    void setBlendState(const BlendState& BS);
    void setRasterizerState(const RasterizerState& RS);
    void setSamplerState(const SamplerState& SS);
    void setVertexShader(const VertexShader& VS);
    void setVertexShaderSlot(const ShaderSlot& Slot);
    void setGeometryShader(const GeometryShader& GS);
    void setGeometryShaderSlot(const ShaderSlot& Slot);
    void setPixelShader(const PixelShader& PS);
    void setPixelShaderSlot(const ShaderSlot& Slot);

    void draw(const RenderMesh& Mesh, UINT IndexCount, UINT BaseIndexLocation=0, INT BaseVertexLocation=0);
    void drawInstanced(UINT InstanceCount, const RenderMesh& Mesh, UINT IndexCountPerMesh, UINT BaseIndexLocation=0, INT BaseVertexLocation=0, UINT StartInstanceLocation=0);

    void finishDraw();

    ///
    /// \brief  有効な描画コンテクストかどうか判定
    ///
    ///         true  : 有効
    ///         false : 無効
    ///
    /// \return 判定結果
    ///
    bool isValid() const noexcept { return context_; }
    operator bool() const noexcept { return context_; }


    ///< ディファードコンテキストを取得
    ID3D11DeviceContext* context() const noexcept { return context_.Get(); }
    ///< 描画コマンドリストを取得
    ID3D11CommandList* commands() const noexcept { return commands_.Get(); }
private :
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> context_;
    Microsoft::WRL::ComPtr<ID3D11CommandList> commands_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_DRAW_CONTEXT_HEADER
// EOF
