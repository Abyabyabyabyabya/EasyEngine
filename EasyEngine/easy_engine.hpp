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

#include <functional>
#include "noncopyable.hpp"
#include "task_manager.hpp"
#include "input_manager.hpp"

namespace easy_engine {

/******************************************************************************

    EasyEngine

******************************************************************************/
///
/// \class  EasyEngine
/// \brief  エンジン本体
///
///         サブシステムのルートでもあります。
///
class EasyEngine final : t_lib::Noncopyable<EasyEngine> {
public :

private :
    EasyEngine();
};
    
} // namespace easy_engine
#endif // !INCLUDED_EGEG_EASY_ENGINE_HEADER_
// EOF
