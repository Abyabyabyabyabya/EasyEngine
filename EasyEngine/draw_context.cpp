// �쐬�� : ��
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
// EOF
