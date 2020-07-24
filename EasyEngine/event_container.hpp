///
/// \file   event_container.hpp
/// \brief  �C�x���g(�֐��I�u�W�F�N�g)�R���e�i�Q��`�w�b�_
/// \author ��
///
/// \note   std::unordered_set<�c>�y�� std::unordered_multiset<�c>�́A�R���p�C�����ʂ�Ȃ����ߖ����B\n
///         std::hash<std::function<�c>>���G���[�̌������Ɨ\�z�B
///
/// \par    ����
///         - 2020/7/23
///             - �w�b�_�ǉ�
///             - EventStack<�c> ��`
///         - 2020/7/24
///             - EventQueue<�c> ��`
///             - EventStack, EventQueue : �C�x���g�Ăяo�����̗�O���A���ڍׂȂ��̂ɕύX
///             - �����Ɉ����Ȃ��Ȃ�A�S�R���e�i�ɂ��ĊȈՋL�q�p�G�C���A�X��ǉ�(�ꕔ��O����)
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
#include <set>

namespace easy_engine {
namespace t_lib {
  namespace impl {
    template <class FTy> struct Event;
    template <class RetTy, class ...ArgTypes>
    struct Event<RetTy(ArgTypes...)> {
        using Type = std::function<RetTy(ArgTypes...)>;
    };
    template <class FTy>
    using EventType = typename Event<FTy>::Type;
  } // namespace impl

/******************************************************************************

    EventStack

******************************************************************************/
///
/// \class  EventStack
/// \brief  �C�x���g�X�^�b�N
///
///         LIFO�̓��������C�x���g�R���e�i�ł��B
///         std::stack�̃��b�p�[�N���X�ł��B�ڍׂ�std::stack�̃��t�@�����X���Q�Ƃ��Ă��������B
///
/// \see https://cpprefjp.github.io/reference/stack.html
///
/// \tparam FTy : �C�x���g�֐��̊֐��^
/// \tparam ContainerTy : std::stack�̓��������ɗp����R���e�i�^
///
/// \details ���^�������� �߂�l�^(�����^���X�g) �̌`�Ŏw�肵�܂��B\n
///          ��.) �߂�l�� void�ŁA������1�� int�󂯎��C�x���g��ێ�����R���e�i��\n
///          EventStack<void(int)> �Ƃ��Đ錾���܂��B
///
template <class FTy, template <class> class ContainerTy=std::deque>
class EventStack : std::stack<impl::EventType<FTy>, ContainerTy<impl::EventType<FTy>>> {
public :
    static_assert(std::is_invocable_v<impl::EventType<FTy>>,
        "EventStack<�c> can only contain invocable object");

  // alias
    using FuncType      = impl::EventType<FTy>;
    using ResultType    = typename FuncType::result_type;
    using ContainerType = std::stack<FuncType, ContainerTy<impl::EventType<FTy>>>;
  // declaration
    using ContainerType::ContainerType;
    using ContainerType::empty;
    using ContainerType::size;
    using ContainerType::top;
    using ContainerType::push;
    using ContainerType::emplace;
    using ContainerType::pop;
    using ContainerType::swap;

    ///
    /// \brief  �擪�̃C�x���g���Ăяo��
    ///
    ///         �ł��V�����ǉ����ꂽ�C�x���g���Ăяo���܂��B
    ///         �Ăяo�����C�x���g�̓R���e�i���Ɏc��܂��B
    ///
    /// \tparam ArgTypes_   : �C�x���g�ɓn�������^���X�g
    /// \param[in] Args     : �C�x���g�ɓn���������X�g
    ///
    /// \return �Ăяo�����C�x���g����Ԃ����l
    ///
    template <class ...ArgTypes_>
    ResultType call(ArgTypes_&& ...Args) {
        if(ContainerType::empty()) error("EventStack::call");

        return ContainerType::top()(std::forward<ArgTypes_>(Args)...);
    }
    
    ///
    /// \brief  �擪�̃C�x���g���Ăяo���Ă���j��
    ///
    ///         �ł��V�����ǉ����ꂽ�C�x���g���Ăяo���܂��B
    ///         �Ăяo�����C�x���g�̓R���e�i����j������܂��B
    ///
    /// \tparam ArgTypes_   : �C�x���g�ɓn�������^���X�g
    /// \param[in] Args     : �C�x���g�ɓn���������X�g
    ///
    /// \return �Ăяo�����C�x���g����Ԃ����l
    ///
    template <class ...ArgTypes_>
    ResultType pop_with_call(ArgTypes_&& ...Args) {
        if(ContainerType::empty()) error("EventStack::pop_with_call");

        auto func = std::move(ContainerType::top());
        ContainerType::pop();
        return func(std::forward<ArgTypes_>(Args)...);
    }

private :
    [[noreturn]] void error(std::string&& Func) const {
        throw std::logic_error(
            "call to invalid event. func: "+Func );
    }
};
    
/******************************************************************************

    EventQueue

******************************************************************************/
///
/// \class  EventQueue
/// \brief  �C�x���g�L���[
///
///         FIFO�̓��������C�x���g�R���e�i�ł��B
///         std::queue�̃��b�p�[�N���X�ł��B�ڍׂ�std::queue�̃��t�@�����X���Q�Ƃ��Ă��������B
///
/// \see https://cpprefjp.github.io/reference/queue/queue.html
///
/// \tparam FTy : �C�x���g�֐��̊֐��^
/// \param[in] ContainerTy : std::queue�̓��������ɗp����R���e�i�^
///
/// \details ���^�������� �߂�l�^(�����^���X�g) �̌`�Ŏw�肵�܂��B\n
///          ��ɂ��āAEventStack<�c>�̏ڍׂ��Q�Ƃ��Ă��������B
///          
/// \see EventStack
///
template <class FTy, template <class> class ContainerTy=std::deque>
class EventQueue : std::queue<impl::EventType<FTy>, ContainerTy<impl::EventType<FTy>>> {
public :
    static_assert(std::is_invocable_v<impl::EventType<FTy>>,
        "EventQueue<�c> can only contain invocable object");

  // alias
    using FuncType = impl::EventType<FTy>;
    using ResultType = typename FuncType::result_type;
    using ContainerType = std::queue<impl::EventType<FTy>, ContainerTy<impl::EventType<FTy>>>;
  // declaration
    using ContainerType::ContainerType;
    using ContainerType::empty;
    using ContainerType::size;
    using ContainerType::push;
    using ContainerType::emplace;
    using ContainerType::pop;
    using ContainerType::swap;

    ///
    /// \brief  �擪�̃C�x���g���擾����
    ///
    /// \return std::queue<�c>::front() �̌Ăяo������
    ///
    [[nodiscard]] typename ContainerType::reference top() noexcept(noexcept(ContainerType::front())) {
        return ContainerType::front();
    }

    /// \brief  �擪�̃C�x���g���擾����
    ///
    /// \return const std::queue<�c>::front() �̌Ăяo������
    ///
    [[nodiscard]] typename ContainerType::const_reference top() const noexcept(noexcept(ContainerType::front())) {
        return ContainerType::front();
    }

    /// \brief  �擪�̃C�x���g���Ăяo��
    ///
    ///         �ێ����Ă���ł��Â��C�x���g���Ăяo���܂��B
    ///         �Ăяo�����C�x���g�̓R���e�i���Ɏc��܂��B
    ///
    /// \tparam ArgTypes_   : �C�x���g�ɓn�������^���X�g
    /// \param[in] Args     : �C�x���g�ɓn���������X�g
    ///
    /// \return �Ăяo�����C�x���g����Ԃ����l
    ///
    template <class ...ArgTypes_>
    ResultType call(ArgTypes_&& ...Args) {
        if(ContainerType::empty()) error("EventQueue::call");

        return ContainerType::front()(std::forward<ArgTypes_>(Args)...);
    }

    ///
    /// \brief  �擪�̃C�x���g���Ăяo���Ă���j��
    ///
    ///         �ێ����Ă���ł��Â��C�x���g���Ăяo���܂��B
    ///         �Ăяo�����C�x���g�̓R���e�i����j������܂��B
    ///
    /// \tparam ArgTypes_   : �C�x���g�ɓn�������^���X�g
    /// \param[in] Args     : �C�x���g�ɓn���������X�g
    ///
    /// \return �Ăяo�����C�x���g����Ԃ����l
    ///
    template <class ...ArgTypes_>
    ResultType pop_with_call(ArgTypes_&& ...Args) {
        if(ContainerType::empty()) error("EventQueue::pop_with_call");

        auto func = std::move(ContainerType::front());
        ContainerType::pop();
        return func(std::forward<ArgTypes_>(Args)...);
    }

private :
    [[noreturn]] void error(std::string&& Func) const {
        throw std::logic_error(
            "call to invalid event. func: "+Func);
    }
};
    
template <class FTy, size_t Size>
using EventArray = std::array<impl::EventType<FTy>, Size>;

template <class FTy, class AllocTy=std::allocator<impl::EventType<FTy>>>
using EventVector = std::vector<impl::EventType<FTy>, AllocTy>;

template <class FTy, class AllocTy=std::allocator<impl::EventType<FTy>>>
using EventList = std::list<impl::EventType<FTy>, AllocTy>;

template <class FTy, class AllocTy=std::allocator<impl::EventType<FTy>>>
using EventForwardList = std::forward_list<impl::EventType<FTy>, AllocTy>;

template <class KeyTy, class FTy, class CompTy=std::less<KeyTy>, class AllocTy=std::allocator<std::pair<const KeyTy, impl::EventType<FTy>>>>
using EventMap = std::map<KeyTy, impl::EventType<FTy>, CompTy, AllocTy>;

template <class KeyTy, class FTy, class CompTy=std::less<KeyTy>, class AllocTy=std::allocator<std::pair<const KeyTy, impl::EventType<FTy>>>>
using EventMultimap = std::multimap<KeyTy, impl::EventType<FTy>, CompTy, AllocTy>;

template <class KeyTy, class FTy, class HasherTy=std::hash<KeyTy>, class KeyeqTy=std::equal_to<KeyTy>, class AllocTy=std::allocator<std::pair<const KeyTy, impl::EventType<FTy>>>>
using EventUnorderedMap = std::unordered_map<KeyTy, impl::EventType<FTy>, HasherTy, KeyeqTy, AllocTy>;

template <class KeyTy, class FTy, class HasherTy=std::hash<KeyTy>, class KeyeqTy=std::equal_to<KeyTy>, class AllocTy=std::allocator<std::pair<const KeyTy, impl::EventType<FTy>>>>
using EventUnorderedMultimap = std::unordered_multimap<KeyTy, impl::EventType<FTy>, HasherTy, KeyeqTy, AllocTy>;

template <class FTy, class Comp=std::less<impl::EventType<FTy>>, class Alloc=std::allocator<impl::EventType<FTy>>>
using EventSet = std::set<impl::EventType<FTy>, Comp, Alloc>;

template <class FTy, class Comp=std::less<impl::EventType<FTy>>, class Alloc=std::allocator<impl::EventType<FTy>>>
using EventMultiset = std::multiset<impl::EventType<FTy>, Comp, Alloc>;

} // namespace t_lib
} // namespace easy_engine

#endif // !INCLUDED_EGEG_TLIB_FACTORY_HEADER_
// EOF
