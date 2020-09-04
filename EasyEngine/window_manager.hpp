///
/// \file   window_manager.hpp
/// \brief  �E�B���h�E�}�l�[�W���[�N���X��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/8/25
///             - �w�b�_�ǉ�
///             - WindowManager ��`
///
/// \note   �R�[���o�b�N�֐��̓o�^�����ɂ���\n
///         �����_�ŕK�v���������Ȃ����ߒ�`���Ă��Ȃ��B
///         �K�v�ɉ����Ē�`����B
///
#ifndef INCLUDED_EGEG_WINDOW_HEADER_
#define INCLUDED_EGEG_WINDOW_HEADER_

#include <type_traits>
#include <memory>
#include <vector>
#include <functional>
#include <Windows.h>

namespace easy_engine {

class EasyEngine;

/******************************************************************************

    WindowManager

******************************************************************************/
///
/// \brief  �E�B���h�E�}�l�[�W���[
///
///         ���̃N���X�ւ̃A�N�Z�X�́AEasyEngine::window()���g�p���Ă��������B
///
class WindowManager {
public :
    friend EasyEngine;

    ///
    /// \brief  �E�B���h�E�n���h�����擾
    ///
    /// \return �E�B���h�E�n���h��
    ///
    HWND handle() const noexcept { return handle_; }
    
    ///
    /// \brief  �R�[���o�b�N�֐���ǉ�
    ///
    ///         �N���X�̃����o�֐��p�ł��B
    ///         �E�B���h�E�C�x���g�����������Ƃ��ɌĂяo�����֐���ǉ����܂��B
    ///
    /// \tparam OwnerTy : �ǉ�����֐��̃I�[�i�[�^
    /// \param[in] Owner : �ǉ�����֐��̃I�[�i�[
    /// \param[in] Callback : �ǉ�����֐�
    ///
    template <class OwnerTy>
    void addCallback(OwnerTy* Owner, void(OwnerTy::*Callback)(HWND, UINT, WPARAM, LPARAM)) {
        using namespace std::placeholders;
        addCallback(std::bind(Callback, Owner, _1, _2, _3, _4));
    }
    ///
    /// \brief  �R�[���o�b�N�֐���ǉ�
    ///
    ///         �E�B���h�E�C�x���g�����������Ƃ��ɌĂяo�����֐���ǉ����܂��B
    ///
    /// \tparam FTy : �ǉ�����֐��^
    /// \param[in] Callback : �ǉ�����֐�
    ///
    template <class FTy>
    void addCallback(FTy&& Callback) {
        callbacks_.emplace_back(std::forward<FTy>(Callback));
    }
private :
    static std::unique_ptr<WindowManager> create();
    WindowManager();

    HWND handle_;
    std::vector<std::function<void(HWND, UINT, WPARAM, LPARAM)>>& callbacks_;
};

} // namespace easy_engine
#endif // !INCLUDED_EGEG_WINDOW_HEADER_
// EOF
