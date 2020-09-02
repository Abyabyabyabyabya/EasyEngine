// çÏê¨é“ : î¬èÍ
/******************************************************************************

    include

******************************************************************************/
#include "texture_resource.hpp"
#include "easy_engine.hpp"


/******************************************************************************

    TextureResource::

******************************************************************************/
easy_engine::g_lib::TextureResource::TextureResource(const D3D11_TEXTURE2D_DESC& Desc, const D3D11_SUBRESOURCE_DATA& Data) {
    EasyEngine::graphics().d3d11Device().CreateTexture2D(&Desc, &Data, &resource_);
}
easy_engine::g_lib::TextureResource::TextureResource(const D3D11_TEXTURE2D_DESC& Desc) {
    EasyEngine::graphics().d3d11Device().CreateTexture2D(&Desc, nullptr, &resource_);
}
// EOF
