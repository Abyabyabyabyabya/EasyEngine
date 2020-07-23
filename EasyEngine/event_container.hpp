///
/// \file   event_container.hpp
/// \brief  EventContainer�N���X��`
/// \author ��
///
/// \par    ����
///         - 2020/7/23
///             - �w�b�_�[�ǉ�
///             - EventStack<�c> ��`
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
    RetTy call(ArgTypes_&& ...Args) {
        if(Container::empty()) throw BadEventCall{};

        return Container::top()(std::forward<ArgTypes_>(Args)...);
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
