// çÏê¨é“ : î¬èÍ
/******************************************************************************

    include

******************************************************************************/
#include "vertex_buffer.hpp"
#include "easy_engine.hpp"


/******************************************************************************

    definition & declaration

******************************************************************************/
namespace vbuffer_ns = easy_engine::g_lib;


/******************************************************************************

    VertexBuffer::

******************************************************************************/
vbuffer_ns::VertexBuffer::VertexBuffer(const UINT Width, const D3D11_SUBRESOURCE_DATA& Data, const UINT Stride) {
    D3D11_BUFFER_DESC desc;
    stride_ = UINT{};
    desc.ByteWidth           = Width;
    desc.Usage               = D3D11_USAGE::D3D11_USAGE_DEFAULT;
    desc.BindFlags           = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
    desc.CPUAccessFlags      = D3D11_CPU_ACCESS_FLAG{};
    desc.MiscFlags           = UINT{};
    desc.StructureByteStride = UINT{};
    if(SUCCEEDED(EasyEngine::graphics().d3d11Device().CreateBuffer(&desc, &Data, &vbuf_)))
        stride_ = Stride;
}
// EOF
