// ì¬ŽÒ : ”Âê
/******************************************************************************

    include

******************************************************************************/
#include "draw_context.hpp"
#include "easy_engine.hpp"


/******************************************************************************

    definition & declaration

******************************************************************************/
namespace dc_ns = easy_engine::g_lib;


/******************************************************************************

    DrawContext::

******************************************************************************/
dc_ns::DrawContext::DrawContext() {
    EasyEngine::graphics().d3d11Device().CreateDeferredContext(0, &context_);
}

dc_ns::TextureResource dc_ns::DrawContext::capture(const TextureResource& Resource) {
    return TextureResource{};
}

void dc_ns::DrawContext::clear() {
    context_->ClearState();
}

void dc_ns::DrawContext::clearLayer(const Layer& Target, const float(&ClearColor)[4]) {
    context_->ClearRenderTargetView(Target.layer(), ClearColor);
}

void dc_ns::DrawContext::setLayer(const Layer& Target, const DepthStencilTexture& DST) {
    ID3D11RenderTargetView* d3d11_target = Target.layer();
    context_->OMSetRenderTargets(1, &d3d11_target, DST.texture());
}

void dc_ns::DrawContext::setLayer(const std::vector<Layer>& Targets, const DepthStencilTexture& DST) {
    std::vector<ID3D11RenderTargetView*> d3d11_targets;
    d3d11_targets.reserve(Targets.size());
    for(auto& target : Targets) {
        d3d11_targets.push_back(target.layer());
    }
    context_->OMSetRenderTargets(d3d11_targets.size(), d3d11_targets.data(), DST.texture());
}

void dc_ns::DrawContext::setBlendState(const BlendState& BS, const float(&BlendFactor)[4], const UINT SampleMask) {
    context_->OMSetBlendState(BS.state(), BlendFactor, SampleMask);
}

void dc_ns::DrawContext::setDepthStencilState(const DepthStencilState& DS, const UINT StencilRef) {
    context_->OMSetDepthStencilState(DS.state(), StencilRef);
}

void dc_ns::DrawContext::setRasterizerState(const RasterizerState& RS) {
    context_->RSSetState(RS.state());
}

void dc_ns::DrawContext::setVertexShader(const VertexShader& VS) {
    context_->VSSetShader(VS.shader(), nullptr, 0);
}
void dc_ns::DrawContext::setVertexShaderSlot(const ShaderSlot& Slot) {

}

void dc_ns::DrawContext::setGeometryShader(const GeometryShader& GS) {
    context_->GSSetShader(GS.shader(), nullptr, 0);
}
void dc_ns::DrawContext::setGeometryShaderSlot(const ShaderSlot& Slot) {

}

void dc_ns::DrawContext::setPixelShader(const PixelShader& PS) {
    context_->PSSetShader(PS.shader(), nullptr, 0);
}
void dc_ns::DrawContext::setPixelShaderSlot(const ShaderSlot& Slot) {

}

void dc_ns::DrawContext::draw(const RenderMesh& Mesh, const UINT NumIndices, const UINT IndexLocation, const INT VertexLocation) {

}

void dc_ns::DrawContext::drawInstanced(const UINT NumInstances, const RenderMesh& Mesh, const UINT NumIndices, const UINT IndexLocation, const INT VertexLocation, UINT InstanceLocation) {

}
// EOF
