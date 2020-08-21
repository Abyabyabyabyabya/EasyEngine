///
/// \fiel   graphics_manager.hpp
/// \brief  �O���t�B�b�N�}�l�[�W���[��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/8/21
///             - �w�b�_�ǉ�
///             - GraphicsManager ��`
///
#ifndef INCLUDED_EGEG_GLIB_GRAPHICS_MANAGER_HEADER_
#define INCLUDED_EGEG_GLIB_GRAPHICS_MANAGER_HEADER_

#include <memory>
#include "noncopyable.hpp"

namespace easy_engine {
class EasyEngine;
   
namespace g_lib {

class GraphicsManager final : t_lib::Noncopyable<GraphicsManager> {
public :
    friend EasyEngine;

private :
    static std::unique_ptr<GraphicsManager> create(); // EasyEngine�N���X�ɂ��Ăяo�����֐�
    GraphicsManager() = default;
};

} // namespace g_lib
} // namespace easy_engine
#endif  // !INCLUDED_EGEG_GLIB_GRAPHICS_MANAGER_HEADER_
// EOF
