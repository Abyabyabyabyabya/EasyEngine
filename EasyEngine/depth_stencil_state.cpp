// çÏê¨é“ : î¬èÍ
/******************************************************************************

    include

******************************************************************************/
#include "depth_stencil_state.hpp"
#include "easy_engine.hpp"
#include "utility_function.hpp"


/******************************************************************************

    definition & declaration

******************************************************************************/
namespace dss_ns = easy_engine::g_lib;
namespace {
    constexpr D3D11_STENCIL_OP kStencilOperationMap[] {
        D3D11_STENCIL_OP_KEEP,     // kKeep
        D3D11_STENCIL_OP_ZERO,     // kZero
        D3D11_STENCIL_OP_REPLACE,  // kReplace
        D3D11_STENCIL_OP_INCR_SAT, // kIncrementSat
        D3D11_STENCIL_OP_DECR_SAT, // kDecrementSat
        D3D11_STENCIL_OP_INVERT,   // kInvert
        D3D11_STENCIL_OP_INCR,     // kIncrement
        D3D11_STENCIL_OP_DECR      // kDecrement
    };

    constexpr D3D11_COMPARISON_FUNC kDepthStencilComparisonMap[] {
        D3D11_COMPARISON_NEVER,         // kNever
        D3D11_COMPARISON_LESS,          // kLess
        D3D11_COMPARISON_EQUAL,         // kEqual
        D3D11_COMPARISON_LESS_EQUAL,    // kLessEqual
        D3D11_COMPARISON_GREATER,       // kGreater
        D3D11_COMPARISON_NOT_EQUAL,     // kNotEqual
        D3D11_COMPARISON_GREATER_EQUAL, // kGreaterEqual
        D3D11_COMPARISON_ALWAYS         // kAlways
    };

    D3D11_DEPTH_STENCIL_DESC convertToD3DDesc(const dss_ns::DepthStencilDesc&);
} // unnamed namespace


/******************************************************************************

    DepthStencilState::

******************************************************************************/
dss_ns::DepthStencilState::DepthStencilState(const dss_ns::DepthStencilDesc& Desc) {
    EasyEngine::graphics().d3d11Device().CreateDepthStencilState(&convertToD3DDesc(Desc), &state_);
}


/******************************************************************************

    Others

******************************************************************************/
namespace { D3D11_DEPTH_STENCIL_DESC convertToD3DDesc(const dss_ns::DepthStencilDesc& Desc) {
    using namespace easy_engine::t_lib;
    auto convertStencilOp = [](const dss_ns::StencilOperationDesc& OpDesc) {
        return D3D11_DEPTH_STENCILOP_DESC {
            kStencilOperationMap[enumValue(OpDesc.fail)],
            kStencilOperationMap[enumValue(OpDesc.depth_fail)],
            kStencilOperationMap[enumValue(OpDesc.pass)],
            kDepthStencilComparisonMap[enumValue(OpDesc.func)]
        };
    };

    return D3D11_DEPTH_STENCIL_DESC {
        Desc.depth_enable ? TRUE : FALSE,
        Desc.depth_write_enable ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO,
        kDepthStencilComparisonMap[enumValue(Desc.depth_func)],
        Desc.stencil_enable ? TRUE : FALSE,
        Desc.stencil_read_mask,
        Desc.stencil_write_mask,
        convertStencilOp(Desc.front_face),
        convertStencilOp(Desc.back_face)
    };
}}
// EOF
