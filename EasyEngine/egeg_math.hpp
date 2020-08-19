///
/// \file   egeg_math.hpp
/// \brief  �Z�p���C�u�����Q
///
///         �R���e�i�̓R���p�C�����萔(constexpr)�ɂȂ邱�Ƃ��ł��܂��B
///         ���Z�ɂ͕����̏������قȂ�֐����g�p���邱�Ƃ��ł��܂��B
///         ���̃w�b�_���C���N���[�h���钼�O�ŁA
///         EGEG_MLIB_USE_SIMD_OPERATION�}�N�����`����ƁASIMD���Z���s���֐����I������܂��B
///         EGEG_MLIB_USE_DEFAULT_NONCOPY_OPERATION�}�N�����`����ƁA�v�Z���ʂ�ۑ�����ꎞ�I�u�W�F�N�g�𐶐����Ȃ�
///         �֐����I������܂��B
///         ���ɉ������Ȃ���΃f�t�H���g�̊֐����w�肳��܂��B
///         �R���p�C�����̃x�N�g�����Z�A�s�񉉎Z���ꕔ�T�|�[�g���Ă��܂����ASIMD���Z���s���֐��ł̓T�|�[�g���Ă��܂���B
///
/// \attention ���O��Ԃ𖾎��I�Ɏw�肷����@�ł͂Ȃ��A�}�N�����`����
///            �g�p����֐���I�������ꍇ�A����ȍ~�̊֐��Ăяo�����S�Ă��̃}�N���ɂ��I���������̂ɂȂ�܂��B\n
///            �ȏ�̗��R����A�w�b�_�ł̃}�N����`���s���Ă͂����܂���B\n
///            �}�N�����`����.cpp�t�@�C���ŁA�قȂ��ނ̊֐����Ăяo�������ꍇ�́A
///            �s�x���O��Ԃ𖾎��I�ɏC�����Ċ֐���I�����Ă��������B\n
///            egeg::m_lib::default_operation�Aegeg::m_lib::default_noncopy_operation�y��egeg::m_lib::simd_operation
///            ���O��Ԃ�using�錾�ɂ��ȗ����Ă͂����܂���B
///
/// \author ��
///
/// \par    ����
///         - 2020/8/3
///             - �w�b�_�ǉ�
///         - 2020/8/19
///             - �w�b�_�R�����g�C��
///
/// \note   ���O��Ԃɂ���\n
///         �K����̖��O��Ԃ𖾎��I�Ȏw��Ȃ��őI���ł���悤�ɂ��Ă���̂ŁA
///         ���̎��̃f�t�H���g�ł͂Ȃ����O��Ԃ�using�錾�ɂ��ȗ��ł���悤�ɂ����
///         �I�[�o�[���[�h�������B���ɂȂ��Ă��܂��B
///         default_noncopy_operation�̊֐��Q�ɂ���\n
///         �x���]���ɂ��e���|�����I�u�W�F�N�g�̐�����}�����Ă��邪�A
///         default_operation�̊֐��Q�ł��R���p�C���ɂ��œK���œ����悤�Ȍ��ʂ����҂ł��邩���B
///         ���s���v�Z�p�֐��ɂ���\n
///         ��肭�����Ă��Ȃ��B�f�t�H���g�ł͎g�p�ł��Ȃ��悤�ɂ��Ă���B\n
///
#ifndef INCLUDED_EGEG_MLIB_EGEGMATH_HEADER_
#define INCLUDED_EGEG_MLIB_EGEGMATH_HEADER_

namespace easy_engine {
namespace m_lib {
#ifdef EGEG_MLIB_USE_SIMD_OPERATION
  inline namespace simd_operation {}
#elif defined EGEG_MLIB_USE_DEFAULT_NONCOPY_OPERATION
  inline namespace default_noncopy_operation {}
#else // default
  inline namespace default_operation {}
#endif // EGEG_MLIB_USE_SIMD_OPERATION
} // namespace m_lib
} // namespace easy_engine

#include "angle.hpp"
#include "mmatrix.hpp"
#include "mmatrix_calc.hpp"
#include "mvector.hpp"
#include "mvector_calc.hpp"

#endif // INCLUDED_EGEG_MLIB_EGEGMATH_HEADER_
// EOF
