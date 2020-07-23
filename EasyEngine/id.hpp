///
/// \file   id.hpp
/// \brief  ID�֘A�N���X��`
/// \author ��
///
/// \par    ����
///         - 2020/7/23
///             - �w�b�_�[�ǉ�
///             - ConstantGenerator, TypeIDGenerator, StringGenerator�y�сA����ɕt������N���X�Ɗ֐��̒�`
///
#ifndef INCLUDED_EGEG_TLIB_ID_HEADER_
#define INCLUDED_EGEG_TLIB_ID_HEADER_

#include <type_traits>
#include <cstdint>

namespace easy_engine {
namespace t_lib {
  namespace impl {
    template <class Ty>
    struct Generator;
    template <auto Value, bool=std::is_enum_v<decltype(Value)>>
    struct Constant;
    template <class Ty>
    struct TypeID;
    template <const char Str[]>
    struct String;
  } // namespace impl

/******************************************************************************

    easy_engine::t_lib::

******************************************************************************/
///
/// \brief  �C���X�^���X���ɈقȂ�ID�𐶐�����
///
/// \tparam Ty          : �C���X�^���X�^
/// \param[in] Instance : �C���X�^���X
///
template <class Ty>
std::uintptr_t uniqueID(const Ty& Instance) noexcept {
    return reinterpret_cast<std::uintptr_t>(&Instance);
}

///
/// \brief  �萔�W�F�l���[�^�[
///
/// �Đ����^�萔�A�X�R�[�v�����񋓌^�萔�A�y�уX�R�[�v�t���񋓌^�萔�ɑΉ����Ă��܂��B
/// ���̑��̌^�ɂ��Ă͑Ή����Ă��܂���B(��. float, char* etc...)
///
/// \tparam Value : ��������萔�l
///
template <auto Value>
using ConstantGenerator = impl::Generator<impl::Constant<Value>>;

///
/// \brief  �^ID�W�F�l���[�^�[
///
/// �^���Ɉ�ӂ�ID�𐶐����܂��B
///
/// \tparam Ty      : ID�ɕϊ�����^
///
template <class Ty>
using TypeIDGenerator = impl::Generator<impl::TypeID<Ty>>;

///
/// \brief  ������W�F�l���[�^�[
///
/// �g�p��) static const chat kName[] = "hogehoge";               <- ������
///        static const StringGenerator<kName> kNameGenerator{}; <- ������̐�����
///
/// \tparam Str : �������镶����
///
/// \attention �w�肷�镶����(��̗�ł���'kName') �� const�ŏC�����ĕύX����Ȃ��悤�ɂ��Ă��������B
///
template <const char Str[]>
using StringGenerator = impl::Generator<impl::String<Str>>;

  /******************************************************************************

        IMPL

  ******************************************************************************/
  namespace impl {
    template <class Ty>
    struct Generator {
      // ������
        using Value = Ty;
        using ValueType = typename Ty::ValueType;

        constexpr operator ValueType() const noexcept {
            return Value::value;
        }
        constexpr ValueType operator()() const noexcept {
            return Value::value;
        }
    };

    template <auto Value>
    struct Constant<Value, true> {
      // �񋓌^�萔
        using ValueType = std::underlying_type_t<decltype(Value)>;

        static constexpr ValueType value = static_cast<ValueType>(Value);
    };
    template <auto Value>
    struct Constant<Value, false> {
      // ��񋓌^�萔
        using ValueType = decltype(Value);

        static_assert(std::is_arithmetic_v<ValueType>, "'Value' must be integral value");
        static constexpr ValueType value = Value;
    };

    template <class Ty>
    struct TypeID {
      // �^���Ɉ�ӂ�ID
        using InstanceType = Ty;
        using ValueType = std::uintptr_t;

        static const ValueType value;
    };
    template <class Ty>
    const typename TypeID<Ty>::ValueType TypeID<Ty>::value {::egeg::t_lib::uniqueID(value)};

    template <const char Str[]>
    struct String {
      // ������
        using ValueType = const char*;
        static const ValueType value;
    };
    template <const char Str[]>
    const typename String<Str>::ValueType String<Str>::value = Str;
  } // namespace impl
} // namespace t_lib
} // namespace easy_engine
#endif // !INCLUDED_EGEG_TLIB_ID_HEADER_
// EOF
