///
/// \file   input_manager.hpp
/// \brief  ���̓}�l�[�W���[��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/8/19
///             - �w�b�_�ǉ�
///             - InputManager ��`
///
#ifndef INCLUDED_EGEG_INPUT_MANAGER_HEADER_
#define INCLUDED_EGEG_INPUT_MANAGER_HEADER_

#include <memory>
#include <unordered_map>
#include "input_device.hpp"
#include "id.hpp"

namespace easy_engine {
class EasyEngine;

namespace i_lib {

/******************************************************************************

    InputManager

******************************************************************************/
///
/// \class  InputManager
/// \brief  ���̓}�l�[�W���[
///
///         �V���O���g���N���X�ł��B
///         ���̃N���X�ւ̃A�N�Z�X�́AEasyEngine�N���X����čs���܂��B
///
class InputManager final {
public :
    friend EasyEngine;

    ~InputManager() = default;

    ///
    /// \brief  ���̓f�o�C�X�Ɛڑ�
    ///
    ///         ���ɐڑ�����Ă���ꍇ�́A�V�����ǉ������Ɋ��ɂ���f�o�C�X��ԋp���܂��B
    ///
    /// \tparam DeviceTy : �ڑ�������̓f�o�C�X
    /// \tparam ArgTypes : ���̓f�o�C�X�̃R���X�g���N�^�ɓ]����������^���X�g
    /// \param[in] Args : ���̓f�o�C�X�̃R���X�g���N�^�ɓ]������������X�g
    ///
    /// \return �ڑ��������̓f�o�C�X�ւ̃|�C���^
    ///
    template <class DeviceTy, class ...ArgTypes>
    const DeviceTy* connect(ArgTypes&& ...Args) {
        if(auto* d = device<DeviceTy>()) return d;
        
        InputDevice* connected = devices_.emplace(
            t_lib::TypeIDGenerator<DeviceTy>{},
            std::make_unique<DeviceTy>(std::forward<ArgTypes>(Args)...)).first->second.get();
        return static_cast<const DeviceTy*>(connected);
    }

    ///
    /// \brief  ���̓f�o�C�X�̐ڑ�������
    ///
    /// \tparam DeviceTy : �ڑ�����������f�o�C�X
    ///
    template <class DeviceTy>
    void disconnect() noexcept(noexcept(devices_.erase(t_lib::TypeIDGenerator<DeviceTy>{}))) {
        devices_.erase(t_lib::TypeIDGenerator<DeviceTy>{});
    }

    ///
    /// \brief  �ڑ�����Ă���f�o�C�X���擾
    ///
    ///         �w�肳�ꂽ�f�o�C�X���ڑ�����Ă��Ȃ��ꍇ��nullptr��ԋp���܂��B
    ///
    /// \tparam DeviceTy : �擾����f�o�C�X
    ///
    /// \return �f�o�C�X�ւ̃|�C���^
    ///
    template <class DeviceTy>
    [[nodiscard]] const DeviceTy* device() const {
        auto find_itr = devices_.find(t_lib::TypeIDGenerator<DeviceTy>{});

        if(find_itr==devices_.end()) return nullptr;
        return static_cast<const DeviceTy*>(find_itr->second.get());
    }

private :
    [[nodiscard]] static std::unique_ptr<InputManager> create(); // EasyEngine�N���X�ɂ��Ăяo�����֐�
    void update();                                               // �㓯 �ێ�����f�o�C�X�����ׂčX�V����
    InputManager() = default;

    std::unordered_map<uintptr_t, std::unique_ptr<InputDevice>> devices_;
};

} // namespace i_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_INPUT_MANAGER_HEADER_
// E0F
