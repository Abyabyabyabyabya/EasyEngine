///
/// \file   task_manager.hpp
/// \brief  タスクマネージャー定義ヘッダ
/// \author 板場
///
/// \par    履歴
///         - 2020/7/25
///             - ヘッダ追加
///             - TaskManager<…> 定義
///
#ifndef INCLUDED_EGEG_TLIB_TASK_MANAGER_HEADER_
#define INCLUDED_EGEG_TLIB_TASK_MANAGER_HEADER_

#include <cstdint>
#include <type_traits>
#include "noncopyable.hpp"
#include "event_container.hpp"

namespace easy_engine {
namespace t_lib {

template <class TaskTy, uint32_t DefaultPriority=0U>
class TaskManager {
public :
    static_assert(std::is_invocable_v<impl::EventType<TaskTy>>, "'TaskTy' must be invocable object type");

    using TaskType = impl::EventType<TaskTy>;

    class TaskInfo final : Noncopyable<TaskInfo> {
    public :
        friend TaskManager;

        TaskInfo() = default;
        TaskInfo(TaskInfo&& Right) noexcept :
            id_{Right.id_}, priority_{Right.priority_}, manager_{Right.manager_} {
            Right.manager_ = nullptr; 
        }
        TaskInfo& operator=(TaskInfo&& Right) noexcept {
            id_ = Right.id_;
            priority_ = Right.priority_;
            manager_ = Right.manager_;
            Right.manager_ = nullptr;

            return *this;
        }
        ~TaskInfo() { if(manager_) manager_->unregisterTask(*this); }

    private :
        TaskInfo(size_t ID, uint32_t Priority, TaskManager* Manager) :
            id_{ID}, priority_{Priority}, manager_{Manager} {}
        size_t id_;
        uint32_t priority_;
        TaskManager* manager_;
    };

    template <class TaskTy_>
    [[nodiscard]] TaskInfo registerTask(TaskTy_&& Task, uint32_t Priority=DefaultPriority) {
        return TaskInfo{insert(Priority, TaskType{std::forward<TaskTy_>(Task)}), Priority, this};
    }

    void unregisterTask(TaskInfo& Info) {
        tasks_[Info.priority_][Info.id_] = TaskType{};
        indices_to_free_[Info.priority_].emplace(Info.id_);

        Info.manager_ = nullptr;
    }

    template <class ...ArgTypes>
    void run(ArgTypes&& ...Args) {
        for(auto& container : tasks_)
          for(auto& task : container.second)
            if(task) task(std::forward<ArgTypes>(Args)...);
    }

private :
    ///
    /// \brief  挿入
    ///
    ///         戻り値は挿入位置
    ///         TaskInfoのIDとして使用する
    ///
    size_t insert(uint32_t Priority, TaskType&& Task) {
        auto& container = tasks_[Priority];

      // 空き領域に挿入
        if(auto free_stack=indices_to_free_.find(Priority); free_stack!=indices_to_free_.end() &&
           free_stack->second.size()) {
            size_t idx_to_free = free_stack->second.top();
            container[idx_to_free] = std::move(Task);
            free_stack->second.pop();
            return idx_to_free;
        }

      // 末尾に挿入
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
