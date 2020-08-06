///
/// \file   egeg_math.hpp
/// \brief  Zpƒ‰ƒCƒuƒ‰ƒŠŒQ
///
/// \author ”Âê
///
/// \par    —š—ğ
///         - 2020/8/3
///             - ƒwƒbƒ_’Ç‰Á
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
