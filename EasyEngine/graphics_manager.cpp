// ì¬Ò : ”Âê
/******************************************************************************

    include

******************************************************************************/
#include "graphics_manager.hpp"
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

/******************************************************************************

    definition & declaration

******************************************************************************/
namespace gm_ns = easy_engine::g_lib;

/******************************************************************************

    GraphicsManager::Impl

******************************************************************************/
struct gm_ns::GraphicsManager::Impl {

};

/******************************************************************************

    GraphicsManager::

******************************************************************************/
gm_ns::GraphicsManager::~GraphicsManager() = default;

std::unique_ptr<gm_ns::GraphicsManager> gm_ns::GraphicsManager::create() {
    std::unique_ptr<GraphicsManager> ptr{new GraphicsManager{}};
    
    ptr->impl_ = std::make_unique<Impl>();
    // ‰Šú‰»

    return ptr;
}


// EOF
