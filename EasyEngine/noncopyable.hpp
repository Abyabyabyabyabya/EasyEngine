///
/// \file   noncopyable.hpp
/// \brief  �R�s�[�֎~�~�b�N�X�C����`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/7/24
///             - �w�b�_�ǉ�
///             - Noncopyable<�c> ��`(����)
///         - 2020/7/25
///             - Noncopyable<�c> ����
///
#ifndef INCLUDED_EGEG_TLIB_NONCOPYABLE_HEADER_
#define INCLUDED_EGEG_TLIB_NONCOPYABLE_HEADER_

namespace easy_engine {
namespace t_lib {
    
/******************************************************************************

    Noncopyable

******************************************************************************/
///
/// \class  Noncopyable
/// \brief  �R�s�[�֎~�~�b�N�X�C��
///
///         �R�s�[�֎~������t�^�������N���X�ŁA���̃~�b�N�X�C����private�p�����Ă��������B
///         �e���v���[�g�N���X�ł��B
///         �N���X���ɐ�p�̃R�s�[�֎~�~�b�N�X�C���𗘗p���邱�ƂŁA�Ȃ�ׂ�EBO�������悤�ɂ��Ă��܂��B
///
/// \tparam DerivedTy : �R�s�[�֎~������t�^����N���X
///
template <class DerivedTy>
class Noncopyable {
public :
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable& operator=(const Noncopyable&) = delete;

protected :
    Noncopyable() = default;
    ~Noncopyable() = default;
};

} // namespace t_lib
} // namespace easy_engine

#endif // !INCLUDED_EGEG_TLIB_NONCOPYABLE_HEADER_
// EOF
