// 作成者 : 板場
/******************************************************************************

    include

******************************************************************************/
#include "index_buffer.hpp"
#include "easy_engine.hpp"


/******************************************************************************

    definition & declaration

******************************************************************************/
namespace ibuffer_ns = easy_engine::g_lib;
namespace ibufimpl_ns = ibuffer_ns::index_buffer_impl;


/******************************************************************************

    IndexBufferData::

******************************************************************************/
ibufimpl_ns::IndexBufferData::IndexBufferData(
  const UINT Size, const D3D11_SUBRESOURCE_DATA& Data, const DXGI_FORMAT Format) {
    format_ = Format;

    D3D11_BUFFER_DESC desc;
    desc.ByteWidth           = Size;
    desc.Usage               = D3D11_USAGE::D3D11_USAGE_DEFAULT;
    desc.BindFlags           = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
    desc.CPUAccessFlags      = UINT{};
    desc.MiscFlags           = UINT{};
    desc.StructureByteStride = UINT{};
    SUCCEEDED(EasyEngine::graphics().d3d11Device().CreateBuffer(&desc, &Data, &ibuf_));
}


/******************************************************************************

    IndexBuffer<>::

******************************************************************************/
ibuffer_ns::IndexBuffer32::IndexBuffer(const std::vector<std::uint32_t>& Data) :
  IndexBufferData{
    sizeof(std::uint32_t)*Data.size(),
    D3D11_SUBRESOURCE_DATA{Data.data(), 0, 0},
    DXGI_FORMAT::DXGI_FORMAT_R32_UINT} {}

template <>
ibuffer_ns::IndexBuffer16::IndexBuffer(const std::vector<std::uint16_t>& Data) :
  IndexBufferData{
    sizeof(std::uint16_t)*Data.size(),
    D3D11_SUBRESOURCE_DATA{Data.data(), 0, 0},
    DXGI_FORMAT::DXGI_FORMAT_R16_UINT} {}

// テンプレートの明示的な宣言
template class ibuffer_ns::IndexBuffer<std::uint32_t>;
template class ibuffer_ns::IndexBuffer<std::uint16_t>;
// EOF
