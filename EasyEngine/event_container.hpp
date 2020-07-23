///
/// \file   event_container.hpp
/// \brief  EventContainerクラス定義
/// \author 板場
///
/// \par    履歴
///         - 2020/7/23
///             - ヘッダー追加
///             - EventStack<…> 定義
///
#ifndef INCLUDED_EGEG_TLIB_FACTORY_HEADER_
#define INCLUDED_EGEG_TLIB_FACTORY_HEADER_

#include <memory>
#include <functional>
#include <stack>
#include <queue>
#include <unordered_map>

namespace easy_engine {
namespace t_lib {

struct BadEventCall{};

/******************************************************************************

    EventStack

******************************************************************************/
template <class EventTy> class EventStack;
template <class RetTy, class ...ArgTypes>
class EventStack<RetTy(ArgTypes...)> : std::stack<std::function<RetTy(ArgTypes...)>> {
public :
    using Container  = std::stack<std::function<RetTy(ArgTypes...)>>;
    using EventType  = std::function<RetTy(ArgTypes...)>;
    using ResultType = RetTy;

    using Container::Container;
    using Container::empty;
    using Container::size;
    using Container::top;
    using Container::push;
    using Container::emplace;
    using Container::pop;
    using Container::swap;

    ///
    /// \brief  先頭のイベントを呼び出す
    ///
    ///         最も新しく追加されたイベントを呼び出します。
    ///         呼び出したイベントはコンテナ内に残ります。
    ///
    /// \tparam ArgTypes_   : イベントに渡す引数型リスト
    /// \param[in] Args     : イベントに渡す引数リスト
    ///
    /// \return 呼び出したイベントから返った値
    ///
    template <class ...ArgTypes_>
    RetTy call(ArgTypes_&& ...Args) {
        if(Container::empty()) throw BadEventCall{};

        return Container::top()(std::forward<ArgTypes_>(Args)...);
    }
    
    ///
    /// \brief  先頭のイベントを呼び出してから破棄
    ///
    ///         最も新しく追加されたイベントを呼び出します。
    ///         呼び出したイベントはコンテナから破棄されます。
    ///
    /// \tparam ArgTypes_   : イベントに渡す引数型リスト
    /// \param[in] Args     : イベントに渡す引数リスト
    ///
    /// \return 呼び出したイベントから返った値
    ///
    template <class ...ArgTypes_>
    RetTy pop_with_call(ArgTypes_&& ...Args) {
        if(Container::empty()) throw BadEventCall{};

        auto func = std::move(Container::top());
        Container::pop();
        return func(std::forward<ArgTypes_>(Args)...);
    }
};
    
/******************************************************************************

    EventQueue

******************************************************************************/
template <class EventTy> class EventQueue;
template <class RetTy, class ...ArgTypes>
class EventQueue<RetTy(ArgTypes...)> : std::queue<std::function<RetTy(ArgTypes...)>> {

};
    
/******************************************************************************

    EventMap

******************************************************************************/
template <class EventTy> class EventMap;
template <class RetTy, class ...Args>
class EventMap<RetTy(Args...)> {

};

} // namespace t_lib
} // namespace easy_engine

#endif // !INCLUDED_EGEG_TLIB_FACTORY_HEADER_
// EOF
