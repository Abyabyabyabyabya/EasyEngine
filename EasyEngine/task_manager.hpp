///
/// \file   task_manager.hpp
/// \brief  �^�X�N�}�l�[�W���[��`�w�b�_
///
/// \author ��
///
/// \note   TaskTy�ɂ��āAbool�ɕϊ��\�ł��邱�Ƃ�\���R���Z�v�g��ǉ����悤�Ƃ�����\n
///         C++17 std::is_convertible_v<�c> �ł͈ÖٓI�ȕϊ��������肪�ł����s���S�B\n
///         C++20 �ł́Astd::convertible_to�ɂ������\�B
///
/// \par    ����
///         - 2020/7/25
///             - �w�b�_�ǉ�
///             - TaskManager<�c> ��`
///         - 2020/7/26
///             - TaskTy �Ɋւ���R���Z�v�g��ǉ�
///             - �R�����g�ǉ�
///
#ifndef INCLUDED_EGEG_TLIB_TASK_MANAGER_HEADER_
#define INCLUDED_EGEG_TLIB_TASK_MANAGER_HEADER_

#include <cstdint>
#include <type_traits>
#include "noncopyable.hpp"
#include "event_container.hpp"

namespace easy_engine {
namespace t_lib {
    
/******************************************************************************

    TaskManager

******************************************************************************/
//
/// \class  TaskManager
/// \brief  �^�X�N�}�l�[�W���[
///
///         �o�b�`�������T�|�[�g���܂��B
///         �^�X�N�͗D��x�ɂ��X�P�W���[�����O����A�D��x�͏������قǍ����A��ɌĂяo����܂��B
///
/// \tparam TaskTy : �o�^����^�X�N�̌^
/// \tparam DefaultPriority : �f�t�H���g�Őݒ肷��D��x
///
/// \details TaskTy �̓t�@���N�^�^���A�߂�l�^(�����^���X�g) �̌`�Ŏw�肵�܂��B
///
/// \attention TaskTy ��bool�ɕϊ��\(�ÖفA�����I��킸)�ł���K�v������܂��B
///
template <class TaskTy, uint32_t DefaultPriority=0U>
class TaskManager {
public :
  // aliases
    using TaskType = event_impl::EventType<TaskTy>;

  // concepts
    static_assert(std::is_default_constructible_v<TaskType>, "'TaskType' must be the default constructible type");
    static_assert(std::is_move_constructible_v<TaskType>, "'TaskType' must be the movable type");
    static_assert(std::is_move_assignable_v<TaskType>, "'TaskType' must be the movable type");

  // nested class
    ///< �^�X�N�o�^���
    class TaskInfo final : Noncopyable<TaskInfo> {
    public :
        friend TaskManager;

        TaskInfo() = default;
        TaskInfo(TaskInfo&& Right) noexcept : id_{Right.id_}, priority_{Right.priority_}, manager_{Right.manager_} {
            Right.manager_ = nullptr; 
        }
        TaskInfo& operator=(TaskInfo&& Right) noexcept {
            id_ = Right.id_;
            priority_ = Right.priority_;
            manager_ = Right.manager_;
            Right.manager_ = nullptr;

            return *this;
        }
        ~TaskInfo() { exitFromManager(); }
        void exitFromManager() { if(manager_) manager_->unregisterTask(*this); }

    private :
        TaskInfo(size_t ID,uint32_t Priority,TaskManager* Manager) : id_{ID}, priority_{Priority}, manager_{Manager} {}
        size_t id_;
        uint32_t priority_;
        TaskManager* manager_;
    };

  // functions
    ///
    /// \brief  �^�X�N��o�^
    ///
    ///         �^�X�N�̗D��x�͏������قǍ����A��ɌĂяo����܂��B
    ///         �߂�l�̃I�u�W�F�N�g�̓^�X�N�̓o�^�����ɕK�v�ł��B
    ///         �܂��A�X�R�[�v���甲����Ǝ����Ń^�X�N�̓o�^����������̂ŁA
    ///         �K�v�ł���΃����o�ϐ��Ƃ��ĕێ�����Ȃǂ��āA�X�R�[�v��L�΂��Ă��������B
    ///
    /// \tparam TaskTy_ : �o�^����^�X�N�^
    /// \param[in] Task : �o�^����^�X�N
    /// \param[in] Priority : �^�X�N�̗D��x
    ///
    /// \return �^�X�N�̓o�^���
    ///
    template <class TaskTy_>
    [[nodiscard]] TaskInfo registerTask(TaskTy_&& Task, uint32_t Priority=DefaultPriority) {
        return TaskInfo{insert(Priority, TaskType{std::forward<TaskTy_>(Task)}), Priority, this};
    }

    ///
    /// \brief  �^�X�N������
    ///
    /// \param[in] Info : �^�X�N�̏��(�o�^���ɐ��������)
    ///
    void unregisterTask(TaskInfo& Info) {
        tasks_[Info.priority_][Info.id_] = TaskType{};
        indices_to_free_[Info.priority_].emplace(Info.id_);

        Info.manager_ = nullptr;
    }

    ///
    /// \brief  �ێ����Ă���S�^�X�N�����s
    ///
    ///         ���s����^�X�N�͕ێ�����܂��B
    ///         ��������K�v������΁AunregisterTask(�c)���Ăяo���ĉ������B
    ///
    /// \tparam ArgTypes : ���s����^�X�N�ɓn�������^���X�g
    /// \param[in] Args  : ���s����^�X�N�ɓn���������X�g
    ///
    /// \note ���������S�]�����Ă��Ȃ����R�́A�����̌Ăяo���ɓn���K�v�����邩��B(move�ɂ��s���h��)
    ///
    template <class ...ArgTypes>
    void run(ArgTypes ...Args) {
        for(auto& container : tasks_)
          for(auto& task : container.second)
            if(task) task(Args...);
    }

private :
    ///
    /// \brief  �}��
    ///
    ///         �߂�l�͑}���ʒu
    ///         TaskInfo��ID�Ƃ��Ďg�p����
    ///
    size_t insert(uint32_t Priority, TaskType&& Task) {
        auto& container = tasks_[Priority];

      // �󂫗̈�ɑ}��
        if(auto free_stack=indices_to_free_.find(Priority); free_stack!=indices_to_free_.end() &&
           free_stack->second.size()) {
            size_t idx_to_free = free_stack->second.top();
            container[idx_to_free] = std::move(Task);
            free_stack->second.pop();
            return idx_to_free;
        }

      // �����ɑ}��
        container.emplace_back(std::move(Task));
        return container.size()-1;
    }
    
    std::map<uint32_t, EventVector<TaskType>> tasks_;        // tasks_[Priority][Task]
    std::map<uint32_t, std::stack<size_t>> indices_to_free_; // indices_to_free_[Priority]
};

} // namespace t_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_TLIB_TASK_MANAGER_HEADER_
// EOF
