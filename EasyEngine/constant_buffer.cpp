// çÏê¨é“ : î¬èÍ
/******************************************************************************

    include

******************************************************************************/
#include "constant_buffer.hpp"
#include "easy_engine.hpp"


/******************************************************************************

    definition & declaration

******************************************************************************/
namespace cbuf_ns = easy_engine::g_lib::constant_buffer_impl;


/******************************************************************************

    ConstantBufferData::

******************************************************************************/
cbuf_ns::ConstantBufferData::ConstantBufferData(const UINT Size, const D3D11_SUBRESOURCE_DATA* Data) {
    D3D11_BUFFER_DESC desc;
    desc.ByteWidth           = Size;
    desc.Usage               = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
    desc.BindFlags           = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
    desc.CPUAccessFlags      = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
    desc.MiscFlags           = UINT{};
    desc.StructureByteStride = UINT{};

    EasyEngine::graphics().d3d11Device().CreateBuffer(&desc, Data, &cbuf_);
}

bool cbuf_ns::ConstantBufferData::update(const void* Data, const size_t Size) {
    D3D11_MAPPED_SUBRESOURCE mpd{};
    if(FAILED(EasyEngine::graphics().d3d11Context().Map(cbuf_.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &mpd)))
        return false;

    memcpy(mpd.pData, Data, Size);

    EasyEngine::graphics().d3d11Context().Unmap(cbuf_.Get(), 0);

    return true;
}
// EOF
