///
/// \file   easy_engine.hpp
/// \brief  エンジンクラス定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/8/19
///             - ヘッダ追加
///             - EasyEngine 定義
///
#ifndef INCLUDED_EGEG_EASY_ENGINE_HEADER_
#define INCLUDED_EGEG_EASY_ENGINE_HEADER_

#include <memory>
#include "noncopyable.hpp"
#include "result.hpp"
#include "window_manager.hpp"
#include "time.hpp"
#include "update_manager.hpp"
#include "input_manager.hpp"
#include "graphic_manager.hpp"

namespace easy_engine {

/******************************************************************************

    EasyEngine

******************************************************************************/
///
/// \brief  エンジン本体
///
///         サブシステムのルートでもあります。
///
class EasyEngine final : t_lib::Noncopyable<EasyEngine> {
public :
    static void run();

    static WindowManager& window() noexcept;
    static const Clock& clock() noexcept;
    static UpdateManager<EasyEngine>& updator() noexcept;
    static i_lib::InputManager& input() noexcept;
    static g_lib::GraphicManager& graphics() noexcept;

private :
    EasyEngine() = default;
    static t_lib::DetailedResult<bool, const char*> startUp();
    static void shutDown() noexcept;

    struct Impl;
    static std::unique_ptr<Impl> impl_;
};
    
} // namespace easy_engine
#endif // !INCLUDED_EGEG_EASY_ENGINE_HEADER_
// EOF
