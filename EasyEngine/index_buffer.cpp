// çÏê¨é“ : î¬èÍ
/******************************************************************************

    include

******************************************************************************/
#include "index_buffer.hpp"
#include "easy_engine.hpp"


/******************************************************************************

    definition & declaration

******************************************************************************/
namespace ibuffer_ns = easy_engine::g_lib;


/******************************************************************************

    IndexBufferData::

******************************************************************************/
ibuffer_ns::IndexBuffer::IndexBuffer(
  const UINT Size, const D3D11_SUBRESOURCE_DATA& Data, const DXGI_FORMAT Format) {
    format_ = Format;

    D3D11_BUFFER_DESC desc;
    desc.ByteWidth           = Size;
    desc.Usage               = D3D11_USAGE::D3D11_USAGE_DEFAULT;
    desc.BindFlags           = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
    desc.CPUAccessFlags      = UINT{};
    desc.MiscFlags           = UINT{};
    desc.StructureByteStride = UINT{};

    EasyEngine::graphics().d3d11Device().CreateBuffer(&desc, &Data, &ibuf_);
}
// EOF
