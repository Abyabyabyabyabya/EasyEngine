// çÏê¨é“ : î¬èÍ
/******************************************************************************

    include

******************************************************************************/
#include "blend_state.hpp"
#include "easy_engine.hpp"
#include "utility_function.hpp"


/******************************************************************************

    definition & declaration

******************************************************************************/
namespace blend_ns = easy_engine::g_lib;
namespace {
    constexpr D3D11_BLEND kBlendCoefficientMap[] {
        D3D11_BLEND_ZERO,              // kZero
        D3D11_BLEND_ONE,               // kOne
        D3D11_BLEND_SRC_COLOR,         // kSrcColor
        D3D11_BLEND_INV_SRC_COLOR,     // kInvSrcColor
        D3D11_BLEND_SRC_ALPHA,         // kSrcAlpha
        D3D11_BLEND_INV_SRC_ALPHA,     // kInvSrcAlpha
        D3D11_BLEND_DEST_ALPHA,        // kDestAlpha
        D3D11_BLEND_INV_DEST_ALPHA,    // kInvDestAlpha
        D3D11_BLEND_DEST_COLOR,        // kDestColor
        D3D11_BLEND_INV_DEST_COLOR,    // kInvDestColor
        D3D11_BLEND_SRC_ALPHA_SAT,     // kSrcAlphaSat
        D3D11_BLEND_BLEND_FACTOR,      // kBlendFactor
        D3D11_BLEND_INV_BLEND_FACTOR,  // kInvBlendFactor
        D3D11_BLEND_SRC1_COLOR,        // kSrc1Color
        D3D11_BLEND_INV_SRC1_COLOR,    // kInvSrc1Color
        D3D11_BLEND_SRC1_ALPHA,        // kSrc1Alpha
        D3D11_BLEND_INV_SRC1_ALPHA,    // kInvSrc1Alpha
    };

    constexpr D3D11_BLEND_OP kBlendOperationMap[] {
        D3D11_BLEND_OP_ADD,          // kAdd
        D3D11_BLEND_OP_SUBTRACT,     // kSubtract
        D3D11_BLEND_OP_REV_SUBTRACT, // kRevSubtract
        D3D11_BLEND_OP_MIN,          // kMin
        D3D11_BLEND_OP_MAX           // kMax
    };

    D3D11_RENDER_TARGET_BLEND_DESC convertToD3DDesc(const blend_ns::BlendDesc&);
    Microsoft::WRL::ComPtr<ID3D11BlendState> 
      createD3D11BlendState(bool, bool, const std::array<blend_ns::BlendDesc, 8U>&);
} // unnamed namespace


/******************************************************************************

    BlendState::

******************************************************************************/
blend_ns::BlendState::BlendState(const blend_ns::BlendDesc& Desc, const bool ATC) {
    state_ = createD3D11BlendState(ATC, false, std::array<BlendDesc, 8U>{Desc});
}

blend_ns::BlendState::BlendState(const std::array<blend_ns::BlendDesc, 8U>& Descs, const bool ATC) {
    state_ = createD3D11BlendState(ATC, true, Descs);
}


/******************************************************************************

    others

******************************************************************************/
namespace { D3D11_RENDER_TARGET_BLEND_DESC convertToD3DDesc(const blend_ns::BlendDesc& Desc) {
    using namespace easy_engine::t_lib;
    return D3D11_RENDER_TARGET_BLEND_DESC {
        Desc.enable ? TRUE : FALSE,
        kBlendCoefficientMap[enumValue(Desc.src_coef)],
        kBlendCoefficientMap[enumValue(Desc.dest_coef)],
        kBlendOperationMap[enumValue(Desc.operation)],
        kBlendCoefficientMap[enumValue(Desc.src_alpha_coef)],
        kBlendCoefficientMap[enumValue(Desc.dest_alpha_coef)],
        kBlendOperationMap[enumValue(Desc.alpha_operation)],
        Desc.write_color_mask
    };
}}

namespace { Microsoft::WRL::ComPtr<ID3D11BlendState> createD3D11BlendState(
  const bool AlphaToCaverage,
  const bool IndependentBlend,
  const std::array<blend_ns::BlendDesc, 8U>& Descs) {
    D3D11_BLEND_DESC desc {
        AlphaToCaverage,
        IndependentBlend,
      { convertToD3DDesc(Descs[0]),
        convertToD3DDesc(Descs[1]),
        convertToD3DDesc(Descs[2]),
        convertToD3DDesc(Descs[3]),
        convertToD3DDesc(Descs[4]),
        convertToD3DDesc(Descs[5]),
        convertToD3DDesc(Descs[6]),
        convertToD3DDesc(Descs[7])}
    };

    Microsoft::WRL::ComPtr<ID3D11BlendState> state;
    easy_engine::EasyEngine::graphics().d3d11Device().CreateBlendState(&desc, &state);

    return state;
}}
// EOF
