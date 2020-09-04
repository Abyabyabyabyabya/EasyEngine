///
/// \file   update_manager.hpp
/// \brief  �X�V�����}�l�[�W���[��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/8/20
///             - �w�b�_�ǉ�
///             - UpdateScheduler ��`
///         - 2020/8/21
///             - ���O�ύX(�t�@�C�����A�N���X���Aetc...)
/// 
#ifndef INCLUDED_EGEG_UPDATE_MANAGER_HEADER_
#define INCLUDED_EGEG_UPDATE_MANAGER_HEADER_

#include "task_manager.hpp"
#include "noncopyable.hpp"
#include "time.hpp"

namespace easy_engine {

namespace impl {
using UpdateFunctorType = std::function<void(Time)>;
} // namespace impl
using UpdateTaskInfo = t_lib::TaskManager<impl::UpdateFunctorType>::TaskInfo;

/******************************************************************************

    UpdateManager

******************************************************************************/
///
/// \brief  �X�V�}�l�[�W���[
///
///         �Q�[���X�V�����Ɋւ���}�l�[�W���[�ł��B
///         �֐��̓o�^�A�X�P�W���[�����O�A�Ăяo�������s���܂��B
///         ������ t_lib::TaskManager<�c>�ł��B
///         �ڍׂɂ��Ă� t_lib::TaskManager<�c>���Q�Ƃ��Ă��������B
/// \see    t_lib::TaskManager
///
/// \tparam AdminTy : �}�l�[�W���[���Ǘ�����N���X�^
///
template <class AdminTy>
class UpdateManager final : t_lib::TaskManager<impl::UpdateFunctorType>, t_lib::Noncopyable<UpdateManager<AdminTy>> {
public :
    friend AdminTy;

    using TaskInfo = t_lib::TaskManager<impl::UpdateFunctorType>::TaskInfo;
    using t_lib::TaskManager<impl::UpdateFunctorType>::unregisterTask;

    ///
    /// \brief  �^�X�N��o�^
    ///
    ///         �X�V������o�^���܂��B
    ///         �o�^����X�V�֐��̓����o�֐��ł���K�v������܂��B
    ///         �o�^��.) �cregisterTask(&hoge, &HogeClass::update, 6U);
    ///         ��registerTask�̖߂�l�͖����ł��܂���B
    ///
    /// \tparam OwnerTy : �֐��̃I�[�i�[�N���X�^
    /// \param[in] Owner    : �֐��̃I�[�i�[
    /// \param[in] Function : �o�^����X�V�֐��ւ̃|�C���^
    /// \param[in] Priority : �֐��̗D��x
    ///
    /// \return �^�X�N�̓o�^���
    ///
    template <class OwnerTy>
    [[nodiscard]] UpdateTaskInfo registerTask(
    OwnerTy* Owner, void(OwnerTy::*Function)(Time), const uint32_t Priority=5U) {
        return t_lib::TaskManager<impl::UpdateFunctorType>::registerTask(
            std::bind(Function, Owner, std::placeholders::_1), Priority);
    }

private :
    static std::unique_ptr<UpdateManager> create() { // AdminTy�N���X�ɂ��Ăяo�����
        return std::unique_ptr<UpdateManager>(new UpdateManager());
    }
    using t_lib::TaskManager<impl::UpdateFunctorType>::run; // �㓯 �o�b�`����
    UpdateManager() = default;
};

} // namespace easy_engine
#endif // !INCLUDED_EGEG_UPDATE_MANAGER_HEADER_
// EOF
