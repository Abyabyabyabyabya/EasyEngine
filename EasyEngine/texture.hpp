//
/// \file   texture.hpp
/// \brief  �e�N�X�`���n���h����`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/8/24
///             - �w�b�_�ǉ�
///             - Texture ��`
///
#ifndef INCLUDED_EGEG_GLIB_TEXTURE_HEADER_
#define INCLUDED_EGEG_GLIB_TEXTURE_HEADER_

#include <type_traits>
#include "noncopyable.hpp"
#include "resource_common.hpp"
#include "easy_engine.hpp"

namespace easy_engine {
namespace g_lib {

// �����d�A�����[�h���Ȃ��悤���ӊ��N
class Texture : public Resource {
public :
    template <class StrTy>
    Texture(StrTy&& FilePath) : Resource{EasyEngine::renderer().textureLoad(std::forward<StrTy>(FilePath))} {}
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_TEXTURE_HEADER_
// EOF
