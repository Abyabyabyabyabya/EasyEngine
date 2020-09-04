///
/// \file   event_container.hpp
/// \brief  イベント(関数オブジェクト)コンテナ群定義ヘッダ
///
///         標準のコンテナに関数オブジェクトをメンバとして持たせたい場合に
///         少し簡単に記述できるようにするための定義群です。
///         Container<std::function<void()>> と記述するところを Container<void()> のように記述することができます。
///
/// \author 板場
///
/// \note   set系コンテナは、コンパイルが通らないため無し。\n
///         std::function<…>が必要な演算子を定義していないことが原因だと予想。
///
/// \par    履歴
///         - 2020/7/23
///             - ヘッダ追加
///             - EventStack<…> 定義
///         - 2020/7/24
///             - EventQueue<…> 定義
///             - EventStack, EventQueue : イベント呼び出し時の例外を、より詳細なものに変更
///             - 引くに引けなくなり、"ほぼ"全てのコンテナについて簡易記述用エイリアスを追加
///         - 2020/7/25
///             - set系コンテナに関する別名を削除
///             - 呼び出し可能オブジェクト型を指定できる EventType<…>を定義
///         - 2020/7/27
///             - 例外送出用、非メンバ関数定義
///         - 2020/8/21
///             - Event コンセプト修正(std::is_invocable_vからstd::is_member_function_pointer_vへ)
///
#ifndef INCLUDED_EGEG_TLIB_FACTORY_HEADER_
#define INCLUDED_EGEG_TLIB_FACTORY_HEADER_

#include <stdexcept>
#include <string>
#include <functional>
#include <stack>
#include <queue>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <map>
#include <unordered_map>

namespace easy_engine {
namespace t_lib {
  namespace event_impl {
    template <class FTy> struct Event {
        static_assert(std::is_member_function_pointer_v<decltype(&FTy::operator())>, 
                      "'FTy' must be invocable object type");
        using Type = FTy;
    };
    template <class RetTy, class ...ArgTypes>
    struct Event<RetTy(ArgTypes...)> {
        using Type = std::function<RetTy(ArgTypes...)>;
    };
    template <class FTy>
    using EventType = typename Event<FTy>::Type;

    [[noreturn]] inline void callError(std::string&& Func) {
        throw std::logic_error("call to invalid event. func: "+Func);
    }
  } // namespace event_impl

/******************************************************************************

    EventStack

******************************************************************************/
///
/// \brief  イベントスタック
///
///         LIFOの動作をするイベントコンテナです。
///         std::stackのラッパークラスです。詳細はstd::stackのリファレンスを参照してください。
///
/// \see https://cpprefjp.github.io/reference/stack.html
///
/// \tparam FTy : イベント関数の関数型
/// \tparam ContainerTy : std::stackの内部実装に用いるコンテナ型
///
/// \details 第一型仮引数は 戻り値型(引数型リスト) の形で指定します。\n
///          例.) 戻り値が voidで、引数に1つの int受け取るイベントを保持するコンテナは\n
///          EventStack<void(int)> として宣言します。
///
template <class FTy, template <class> class ContainerTy=std::deque>
class EventStack : std::stack<event_impl::EventType<FTy>, ContainerTy<event_impl::EventType<FTy>>> {
public :
  // aliases
    using FuncType      = event_impl::EventType<FTy>;
    using ResultType    = typename FuncType::result_type;
    using ContainerType = std::stack<FuncType, ContainerTy<event_impl::EventType<FTy>>>;
  // declarations
    using ContainerType::ContainerType;
    using ContainerType::empty;
    using ContainerType::size;
    using ContainerType::top;
    using ContainerType::push;
    using ContainerType::emplace;
    using ContainerType::pop;
    using ContainerType::swap;

  // functions
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
    ResultType call(ArgTypes_&& ...Args) {
        if(ContainerType::empty()) event_impl::callError("EventStack::call");

        return ContainerType::top()(std::forward<ArgTypes_>(Args)...);
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
    ResultType pop_with_call(ArgTypes_&& ...Args) {
        if(ContainerType::empty()) event_impl::callError("EventStack::pop_with_call");

        auto func = std::move(ContainerType::top());
        ContainerType::pop();
        return func(std::forward<ArgTypes_>(Args)...);
    }
};
    
/******************************************************************************

    EventQueue

******************************************************************************/
///
/// \brief  イベントキュー
///
///         FIFOの動作をするイベントコンテナです。
///         std::queueのラッパークラスです。詳細はstd::queueのリファレンスを参照してください。
///
/// \see https://cpprefjp.github.io/reference/queue/queue.html
///
/// \tparam FTy : イベント関数の関数型
/// \param[in] ContainerTy : std::queueの内部実装に用いるコンテナ型
///
/// \details 第一型仮引数は 戻り値型(引数型リスト) の形で指定します。\n
///          例について、EventStack<…>の詳細を参照してください。
///          
/// \see EventStack
///
template <class FTy, template <class> class ContainerTy=std::deque>
class EventQueue : std::queue<event_impl::EventType<FTy>, ContainerTy<event_impl::EventType<FTy>>> {
public :
  // alias
    using FuncType = event_impl::EventType<FTy>;
    using ResultType = typename FuncType::result_type;
    using ContainerType = std::queue<event_impl::EventType<FTy>, ContainerTy<event_impl::EventType<FTy>>>;
  // declaration
    using ContainerType::ContainerType;
    using ContainerType::empty;
    using ContainerType::size;
    using ContainerType::push;
    using ContainerType::emplace;
    using ContainerType::pop;
    using ContainerType::swap;

    ///
    /// \brief  先頭のイベントを取得する
    ///
    /// \return std::queue<…>::front() の呼び出し結果
    ///
    [[nodiscard]] typename ContainerType::reference top() noexcept(noexcept(ContainerType::front())) {
        return ContainerType::front();
    }

    /// \brief  先頭のイベントを取得する
    ///
    /// \return const std::queue<…>::front() の呼び出し結果
    ///
    [[nodiscard]] typename ContainerType::const_reference top() const noexcept(noexcept(ContainerType::front())) {
        return ContainerType::front();
    }

    /// \brief  先頭のイベントを呼び出す
    ///
    ///         保持している最も古いイベントを呼び出します。
    ///         呼び出したイベントはコンテナ内に残ります。
    ///
    /// \tparam ArgTypes_   : イベントに渡す引数型リスト
    /// \param[in] Args     : イベントに渡す引数リスト
    ///
    /// \return 呼び出したイベントから返った値
    ///
    template <class ...ArgTypes_>
    ResultType call(ArgTypes_&& ...Args) {
        if(ContainerType::empty()) event_impl::callError("EventQueue::call");

        return ContainerType::front()(std::forward<ArgTypes_>(Args)...);
    }

    ///
    /// \brief  先頭のイベントを呼び出してから破棄
    ///
    ///         保持している最も古いイベントを呼び出します。
    ///         呼び出したイベントはコンテナから破棄されます。
    ///
    /// \tparam ArgTypes_   : イベントに渡す引数型リスト
    /// \param[in] Args     : イベントに渡す引数リスト
    ///
    /// \return 呼び出したイベントから返った値
    ///
    template <class ...ArgTypes_>
    ResultType pop_with_call(ArgTypes_&& ...Args) {
        if(ContainerType::empty()) event_impl::callError("EventQueue::pop_with_call");

        auto func = std::move(ContainerType::front());
        ContainerType::pop();
        return func(std::forward<ArgTypes_>(Args)...);
    }
};


/******************************************************************************

    other containers

******************************************************************************/
template <class FTy, size_t Size>
using EventArray = std::array<event_impl::EventType<FTy>, Size>;

template <class FTy, class AllocTy=std::allocator<event_impl::EventType<FTy>>>
using EventVector = std::vector<event_impl::EventType<FTy>, AllocTy>;

template <class FTy, class AllocTy=std::allocator<event_impl::EventType<FTy>>>
using EventList = std::list<event_impl::EventType<FTy>, AllocTy>;

template <class FTy, class AllocTy=std::allocator<event_impl::EventType<FTy>>>
using EventForwardList = std::forward_list<event_impl::EventType<FTy>, AllocTy>;

template <class KeyTy, class FTy, class CompTy=std::less<KeyTy>, class AllocTy=std::allocator<std::pair<const KeyTy, event_impl::EventType<FTy>>>>
using EventMap = std::map<KeyTy, event_impl::EventType<FTy>, CompTy, AllocTy>;

template <class KeyTy, class FTy, class CompTy=std::less<KeyTy>, class AllocTy=std::allocator<std::pair<const KeyTy, event_impl::EventType<FTy>>>>
using EventMultimap = std::multimap<KeyTy, event_impl::EventType<FTy>, CompTy, AllocTy>;

template <class KeyTy, class FTy, class HasherTy=std::hash<KeyTy>, class KeyeqTy=std::equal_to<KeyTy>, class AllocTy=std::allocator<std::pair<const KeyTy, event_impl::EventType<FTy>>>>
using EventUnorderedMap = std::unordered_map<KeyTy, event_impl::EventType<FTy>, HasherTy, KeyeqTy, AllocTy>;

template <class KeyTy, class FTy, class HasherTy=std::hash<KeyTy>, class KeyeqTy=std::equal_to<KeyTy>, class AllocTy=std::allocator<std::pair<const KeyTy, event_impl::EventType<FTy>>>>
using EventUnorderedMultimap = std::unordered_multimap<KeyTy, event_impl::EventType<FTy>, HasherTy, KeyeqTy, AllocTy>;

} // namespace t_lib
} // namespace easy_engine

#endif // !INCLUDED_EGEG_TLIB_FACTORY_HEADER_
// EOF
