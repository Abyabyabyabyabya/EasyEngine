///
/// \file   resource_common.hpp
/// \brief  リソース共通ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/24
///             - ヘッダ追加
///             - ResourceHandle 宣言
///
#ifndef INCLUDED_EGEG_RESOURCE_COMMON_HEADER_
#define INCLUDED_EGEG_RESOURCE_COMMON_HEADER_

#include <cstdint>
#include "easy_engine.hpp"

namespace easy_engine {

using ResourceHandle = std::uintptr_t;

class Resource {
public :
    Resource(const ResourceHandle Handle = ResourceHandle{}) noexcept : handle_{Handle} {}
    virtual ~Resource() { if(isValid()) EasyEngine::renderer().resourceRelease(handle()); }
    Resource(const Resource& Right) : handle_{Right.handle()} {
        addRef();
    }
    Resource& operator=(const Resource& Right) {
        handle_ = Right.handle();
        addRef();
        return *this;
    }
    Resource(Resource&& Right) noexcept : handle_{Right.handle()} {
        Right.handle_ = ResourceHandle{};
    }
    Resource& operator=(Resource&& Right) noexcept {
        handle_ = Right.handle();
        Right.handle_ = ResourceHandle{};
        return *this;
    }

    bool isValid() const noexcept { return handle(); }
    operator bool() const noexcept { isValid(); }

protected :
    ResourceHandle handle() const noexcept { return handle_; }

private :
    void addRef() {
        if(isValid())
            EasyEngine::renderer().resourceAddRef(handle());
    }
    ResourceHandle handle_;
};

} // namespace easy_engine
#endif // !INCLUDED_EGEG_RESOURCE_COMMON_HEADER_
// EOF
