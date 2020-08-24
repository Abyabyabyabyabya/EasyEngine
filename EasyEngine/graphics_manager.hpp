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

#include <cstdint>
#include <memory>
#include <string>
#include "noncopyable.hpp"
#include "time.hpp"

namespace easy_engine {
class EasyEngine;
   
namespace g_lib {
using ResourceHandle = std::uintptr_t;

class GraphicsManager final : t_lib::Noncopyable<GraphicsManager> {
public :
    friend EasyEngine;

    ~GraphicsManager();

    ResourceHandle textureLoad(std::string FilePath);

    ResourceHandle modelLoad(std::string FilePath);
    void modelUpdate(ResourceHandle, Time);
    void modelSetAnimation(ResourceHandle, int);

    ResourceHandle shaderLoad(std::string FilePath);
    void shaderSetTexture(ResourceHandle, ResourceHandle*);
    void shaderSetSampler(ResourceHandle, void*);

    void resourceAddRef(ResourceHandle);
    void resourceRelease(ResourceHandle);

private :
    static std::unique_ptr<GraphicsManager> create(); // EasyEngine�N���X�ɂ��Ăяo�����֐�
    GraphicsManager() = default;

    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace g_lib
} // namespace easy_engine
#endif  // !INCLUDED_EGEG_GLIB_GRAPHICS_MANAGER_HEADER_
// EOF
