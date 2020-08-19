///
/// \file   id.hpp
/// \brief  ID関連クラス定義ヘッダ
///
/// \author 板場
///
/// \par    履歴
///         - 2020/7/23
///             - ヘッダ追加
///             - ConstantGenerator, TypeIDGenerator, StringGenerator及び、それに付随するクラスと関数を定義
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
/// \brief  インスタンス毎に異なるIDを生成する
///
/// \tparam Ty          : インスタンス型
/// \param[in] Instance : インスタンス
///
template <class Ty>
std::uintptr_t uniqueID(const Ty& Instance) noexcept {
    return reinterpret_cast<std::uintptr_t>(&Instance);
}

///
/// \brief  定数ジェネレーター
///
/// 汎整数型定数、スコープ無し列挙型定数、及びスコープ付き列挙型定数に対応しています。\n
/// その他の型については対応していません。(例. float, char* etc...)
///
/// \tparam Value : 生成する定数値
///
template <auto Value>
using ConstantGenerator = impl::Generator<impl::Constant<Value>>;

///
/// \brief  型IDジェネレーター
///
/// 型毎に一意なIDを生成します。
///
/// \tparam Ty      : IDに変換する型
///
template <class Ty>
using TypeIDGenerator = impl::Generator<impl::TypeID<Ty>>;

///
/// \brief  文字列ジェネレーター
///
/// 使用例)\n
///         static const chat kName[] = "hogehoge";               <- 文字列\n
///         static const StringGenerator<kName> kNameGenerator{}; <- 文字列の生成者
///
/// \tparam Str : 生成する文字列
///
/// \attention 指定する文字列(上の例でいう'kName') は constで修飾して変更されないようにしてください。
///
template <const char Str[]>
using StringGenerator = impl::Generator<impl::String<Str>>;

  /******************************************************************************

        IMPL

  ******************************************************************************/
  namespace impl {
    template <class Ty>
    struct Generator {
      // 生成者
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
      // 列挙型定数
        using ValueType = std::underlying_type_t<decltype(Value)>;

        static constexpr ValueType value = static_cast<ValueType>(Value);
    };
    template <auto Value>
    struct Constant<Value, false> {
      // 非列挙型定数
        using ValueType = decltype(Value);

        static_assert(std::is_arithmetic_v<ValueType>, "'Value' must be integral value");
        static constexpr ValueType value = Value;
    };

    template <class Ty>
    struct TypeID {
      // 型毎に一意なID
        using InstanceType = Ty;
        using ValueType = std::uintptr_t;

        static const ValueType value;
    };
    template <class Ty>
    const typename TypeID<Ty>::ValueType TypeID<Ty>::value {uniqueID(value)};

    template <const char Str[]>
    struct String {
      // 文字列
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
