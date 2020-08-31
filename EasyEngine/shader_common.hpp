///
/// \file   shader_common.hpp
/// \brief  シェーダー共通ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/31
///
#ifndef INCLUDED_EGEG_GLIB_SHADER_COMMON_HEADER_
#define INCLUDED_EGEG_GLIB_SHADER_COMMON_HEADER_

#include <d3d11.h>
#include <wrl.h>

namespace easy_engine {
namespace g_lib {

  namespace shader_impl {
    struct Blob {
        char* bytecode{};
        size_t size{};

        operator bool() const noexcept { return bytecode; }
        Blob() = default;
        Blob(const size_t Size) : bytecode{new char[Size]}, size{Size} {}
        ~Blob() { delete[] bytecode; }
        Blob(const Blob&) = delete;
        Blob& operator=(const Blob&) = delete;
        Blob(Blob&& Right) noexcept : bytecode{Right.bytecode}, size{Right.size} {
            Right.bytecode = nullptr;
        }
        Blob& operator=(Blob&& Right) noexcept {
            bytecode = Right.bytecode;
            size     = Right.size;
            Right.bytecode = nullptr;
            return *this;
        }
    };
    Blob loadShaderFile(const char* FilePath);

  } // namespace shader_impl

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_SHADER_COMMON_HEADER_
// EOF
