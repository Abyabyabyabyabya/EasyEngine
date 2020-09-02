///
/// \file   texture_resource.hpp
/// \brief  �e�N�X�`�����\�[�X��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/9/2
///             - �w�b�_�ǉ�
///             - TextureResource ��`
///
#ifndef INCLUDED_EGEG_GLIB_TEXTURE_RESOURCE_HEADER_
#define INCLUDED_EGEG_GLIB_TEXTURE_RESOURCE_HEADER_

#include <d3d11.h>
#include <wrl.h>

namespace easy_engine {
namespace g_lib {

///
/// \class  TextureResource
/// \brief  �e�N�X�`�����\�[�X
///
class TextureResource {
public :
    virtual ~TextureResource() = default;

    ///
    /// \brief  �f�t�H���g�̃R���X�g���N�^
    ///
    ///         �e�N�X�`���͍쐬���܂���B
    ///
    TextureResource() = default;

    ///
    /// \brief  �e�N�X�`���̍쐬�𔺂��R���X�g���N�^
    ///
    /// \param[in] �e�N�X�`���̒�`
    /// \param[in] �e�N�X�`���̏����f�[�^(�ȗ��ŏ����f�[�^�Ȃ�)
    ///
    TextureResource(const D3D11_TEXTURE2D_DESC&, const D3D11_SUBRESOURCE_DATA&);
    TextureResource(const D3D11_TEXTURE2D_DESC&);

    ///
    /// \brief  �L���ȃe�N�X�`�����\�[�X���ǂ�������
    ///
    ///         true  : �L��
    ///         false : ����
    ///
    /// \return ���茋��
    ///
    bool isValid() const noexcept { return resource_; }
    operator bool() const noexcept { return isValid(); }


    ///< ���\�[�X���擾
    ID3D11Texture2D* resource() const noexcept { return resource_.Get(); }
protected :
    Microsoft::WRL::ComPtr<ID3D11Texture2D> resource_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_TEXTURE_RESOURCE_HEADER_
// EOF
