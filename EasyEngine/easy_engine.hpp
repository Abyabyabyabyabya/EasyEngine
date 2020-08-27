///
/// \file   easy_engine.hpp
/// \brief  �G���W���N���X��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/8/19
///             - �w�b�_�ǉ�
///             - EasyEngine ��`
///
#ifndef INCLUDED_EGEG_EASY_ENGINE_HEADER_
#define INCLUDED_EGEG_EASY_ENGINE_HEADER_

#include <memory>
#include "noncopyable.hpp"
#include "result.hpp"
#include "window_manager.hpp"
#include "time.hpp"
#include "update_manager.hpp"
#include "input_manager.hpp"
#include "graphic_manager.hpp"

namespace easy_engine {

/******************************************************************************

    EasyEngine

******************************************************************************/
///
/// \class  EasyEngine
/// \brief  �G���W���{��
///
///         �T�u�V�X�e���̃��[�g�ł�����܂��B
///
class EasyEngine final : t_lib::Noncopyable<EasyEngine> {
public :
    static void run();

    static WindowManager& window() noexcept;
    static const Clock& clock() noexcept;
    static UpdateManager<EasyEngine>& updator() noexcept;
    static i_lib::InputManager& input() noexcept;
    static g_lib::GraphicManager& graphics() noexcept;

private :
    EasyEngine() = default;
    static t_lib::DetailedResult<bool, const char*> startUp();
    static void shutDown() noexcept;

    struct Impl;
    static std::unique_ptr<Impl> impl_;
};
    
} // namespace easy_engine
#endif // !INCLUDED_EGEG_EASY_ENGINE_HEADER_
// EOF
