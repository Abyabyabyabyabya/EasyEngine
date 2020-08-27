///
/// \file   layer.hpp
/// \brief  ���C���[��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/8/27
///             - �w�b�_�ǉ�
///             - Layer ��`
///
#ifndef INCLUDED_EGEG_GLIB_LAYER_HEADER_
#define INCLUDED_EGEG_GLIB_LAYER_HEADER_

#include "texture.hpp"

namespace easy_engine {
namespace g_lib {

///
/// \class  Layer
/// \brief  ���C���[(�V�F�[�_�[���\�[�X & �����_�[�^�[�Q�b�g)
///
class Layer : public Texture {
public :
    Layer() = default;

    ///
    /// \brief  �R���X�g���N�^
    ///
    /// \param[in] Width         : ���C���[����
    /// \param[in] Height        : ���C���[�c��
    /// \param[in] SampleCount   : 1�s�N�Z��������̃T���v����
    /// \param[in] SampleQuality : �}���`�T���v���̉掿���x��
    ///
    Layer(UINT Width, UINT Height, UINT SampleCount=1U, UINT SampleQuality=0U);

    ///
    /// \brief  �L���ȃ��C���[���ǂ�������
    ///
    ///         true  : �L��
    ///         false : ����
    ///
    /// \return ���茋��
    ///
    bool isValid() const noexcept {
        return Texture::isValid() && layer_;
    }
    operator bool() const noexcept {
        return isValid();
    }


    ///< ���C���[���擾
    ID3D11RenderTargetView* layer() const noexcept { layer_.Get(); }
protected :
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> layer_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_LAYER_HEADER_
// EOF
