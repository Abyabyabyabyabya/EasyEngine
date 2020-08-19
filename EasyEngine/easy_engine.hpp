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

#include <functional>
#include "noncopyable.hpp"
#include "task_manager.hpp"
#include "input_manager.hpp"

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

private :
    EasyEngine();
};
    
} // namespace easy_engine
#endif // !INCLUDED_EGEG_EASY_ENGINE_HEADER_
// EOF
