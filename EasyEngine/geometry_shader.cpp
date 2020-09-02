// çÏê¨é“ : î¬èÍ
/******************************************************************************

    include

******************************************************************************/
#include "geometry_shader.hpp"
#include "easy_engine.hpp"


/******************************************************************************

    GeometryShader::

******************************************************************************/
easy_engine::g_lib::GeometryShader::GeometryShader(const char* FilePath) {
    if(auto blob = shader_impl::loadShaderFile(FilePath))
        EasyEngine::graphics().d3d11Device().CreateGeometryShader(blob.bytecode, blob.size, nullptr, &shader_);
}
// EOF
