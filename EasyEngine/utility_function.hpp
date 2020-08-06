///
/// \file   utility_function.hpp
/// \brief  �����֗��ȃe���v���[�g�֐��Q��`�w�b�_
///
/// \author ��
///
/// \par    ����
///         - 2020/7/27
///             - �w�b�_�ǉ�
///             - arraySize<�c>() ��`
///             - enumValue<�c>() ��`
///
#ifndef INCLUDED_EGEG_TLIB_UTILITY_FUNCTION_HEADER_
#define INCLUDED_EGEG_TLIB_UTILITY_FUNCTION_HEADER_

#include <type_traits>

namespace easy_engine {
namespace t_lib {

///
/// \brief  �z��̗v�f�����擾����
///
///         �g�p��)
///          int arr[10];
///          size_t size = arraySize(arr);  �c size == �u10�v
///
/// \tparam ElemTy : �z��̗v�f�^
/// \tparam Size   : �z��̗v�f��
/// \param[in]     : �v�f�����擾����z��
///
/// \return �z��̗v�f��
///
template <class ElemTy, size_t Size>
inline constexpr size_t arraySize(const ElemTy(&)[Size]) noexcept {
    return Size;
}

///
/// \brief  ��b�^�ɕϊ������񋓎q���擾����
///
///         �X�R�[�v�Ȃ��񋓌^�ł��X�R�[�v�t���񋓌^�ł����삵�܂��B
///         �g�p��)
///          enum class Hoge { Koreha, Rekkyosi, Dayo };
///             �c ���� �c
///          auto v = enumValue(Hoge::Koreha);
///
/// \tparam EnumTy   : �񋓌^
/// \param[in] Value : �ϊ�����񋓎q
///
/// \return ��b�^�ɕϊ������񋓎q�̒l
///
/// \attention Value�͗񋓎q�ł���K�v������܂��B
///
template <class EnumTy>
inline constexpr auto enumValue(EnumTy Value) noexcept {
    return static_cast<std::underlying_type_t<EnumTy>>(Value);
}

} // namespace t_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_TLIB_UTILITY_FUNCTION_HEADER_
// EOF
