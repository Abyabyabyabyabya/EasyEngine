///
/// \file   shader_slot.hpp
/// \brief  �V�F�[�_�[���N���X��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/8/28
///             - �w�b�_�ǉ�
///             - Shader ��`
///         - 2020/8/31
///             - �w�b�_���ύX(shader.hpp -> shader_slot.hpp)
///             - �N���X���ύX(Shader -> ShaderSlot)
///
#ifndef INCLUDED_EGEG_GLIB_SHADER_SLOT_HEADER_
#define INCLUDED_EGEG_GLIB_SHADER_SLOT_HEADER_

#include <map>
#include <d3d11.h>
#include <wrl.h>
#include "constant_buffer.hpp"
#include "texture.hpp"

namespace easy_engine {
namespace g_lib {

///
/// \class  ShaderSlot
/// \brief  �V�F�[�_�[�X���b�g
///
///         �V�F�[�_�[�ւ̓��͂��i�[���܂��B
///
class ShaderSlot {
public :
    virtual ~ShaderSlot() = default;

    ///
    /// \brief  �萔���Z�b�g
    ///
    ///         �����̒萔����x�ɃZ�b�g���邱�Ƃ��ł��܂��B
    ///         ���̏ꍇ�AStartSlot���珇��1���X���b�g������Ă����܂��B
    ///         �X���b�g���΂��ăZ�b�g�������ꍇ�A�����̌Ăяo���ɕ����Ă��������B
    ///
    /// \tparam DataTy : �Z�b�g����萔�̃f�[�^�^
    ///
    /// \param[in] StartSlot : �Z�b�g�J�n�X���b�g
    /// \param[in] Constant  : StartSlot�ɃZ�b�g����萔
    /// \param[in] Constants : �c��̒萔���X�g
    ///
    template <class DataTy, class ...Rest>
    void setConstant(const UINT StartSlot, const ConstantBuffer<DataTy>& Constant, Rest ...Constants) {
        setConstant(StartSlot, Constant.buffer());
        setConstant(StartSlot+1, Constants...);
    }
    
    ///
    /// \brief  �e�N�X�`�����Z�b�g
    ///
    ///         �ڍׂ� setConstant �Ɠ��l�ł��B
    ///
    /// \param[in] StartSlot : �Z�b�g�J�n�X���b�g
    /// \param[in] Texture   : StartSlot�ɃZ�b�g����e�N�X�`��
    /// \param[in] Textures  : �c��̃e�N�X�`�����X�g
    ///
    template <class ...Rest>
    void setTexture(const UINT StartSlot, const Texture& Texture, Rest ...Textures) {
        setTexture(StartSlot, Texture.texture());
        setTexture(StartSlot+1, Textures...);
    }

    // TODO : sampler


    ///< �X���b�g�ԍ��Ƀ}�b�v���ꂽ�萔�o�b�t�@���擾
    const std::map<UINT, Microsoft::WRL::ComPtr<ID3D11Buffer>>& constants() const noexcept { return constants_; }
    ///< �X���b�g�ԍ��Ƀ}�b�v���ꂽ�e�N�X�`�����擾
    const std::map<UINT, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>& textures() const noexcept { return textures_; }
    ///< �X���b�g�ԍ��Ƀ}�b�v���ꂽ�T���v���[���擾
    const std::map<UINT, Microsoft::WRL::ComPtr<ID3D11SamplerState>>& samplers() const noexcept { return samplers_; }
protected :
    ShaderSlot() = default;
private :
    void setConstant(const UINT) const noexcept {}
    void setConstant(const UINT Slot, ID3D11Buffer* Buffer) { constants_[Slot] = Buffer; }
    void setTexture(const UINT) const noexcept {}
    void setTexture(const UINT Slot, ID3D11ShaderResourceView* View) { textures_[Slot] = View; }
    void setSampler(const UINT) const noexcept {}
    void setSampler(const UINT Slot, ID3D11SamplerState* State) { samplers_[Slot] = State; }

    std::map<UINT, Microsoft::WRL::ComPtr<ID3D11Buffer>> constants_;
    std::map<UINT, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> textures_;
    std::map<UINT, Microsoft::WRL::ComPtr<ID3D11SamplerState>> samplers_;
};

} // namespace g_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_GLIB_SHADER_SLOT_HEADER_
// EOF
