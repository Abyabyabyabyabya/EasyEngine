// 作成者 : 板場
/******************************************************************************

    include

******************************************************************************/
#include "shader_common.hpp"
#include <fstream>


/******************************************************************************

    definition & declaration

******************************************************************************/
namespace shader_ns = easy_engine::g_lib::shader_impl;


/******************************************************************************

    function

******************************************************************************/
shader_ns::Blob shader_ns::loadShaderFile(const char* FilePath) {
    std::fstream stream{FilePath, std::ios::binary|std::ios::in};
    if(!stream) return Blob{};

    // データ格納用バッファを作成
    stream.seekg(0, std::ios::end);
    const auto end = stream.tellg();
    stream.clear();
    stream.seekg(0, std::ios::beg);
    const size_t size = static_cast<size_t>(end - stream.tellg());
    Blob buffer{size};

    stream.read(buffer.bytecode, buffer.size);

    return buffer;
}
// EOF
