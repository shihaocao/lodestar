// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_ALGORITHMS_BACKWARD_SUB_HPP_
#define LIN_INCLUDE_ALGORITHMS_BACKWARD_SUB_HPP_

#include "../core/core.hpp"

#include <cassert>
#include <type_traits>

// TODO : Evaluate again whether or not U and Y could be of type
//        internal::Stream<...>

namespace lin
{
namespace internal
{

/** @struct can_backward_sub
 *  True if the backward substitution function can be called on the specified
 *  template and false otherwise. To be compatible, tX and tY must have
 *  compatible traits. Furthermore, the product of tU and tX must exist and
 *  result in the same traits as tY. */
template <class tU, class tX, class tY>
struct can_backward_sub : public std::integral_constant<bool, (
    are_traits_equal<tX, tY>::value && are_traits_equal<Multiply<tU, tX>, tY>::value
  )> { };

}  // namespace internal

/** @fn backward_sub
 *  @param[in] U n by n upper-right triangular matrix.
 *  @param[out] X n by m matrix storing the solution (can be a vector).
 *  @param[in] Y n by m matrix (can be a vector).
 * 
 *  Solves the following linear system of equations U * X = Y where U and Y are
 *  given and U is knows to be an upper triangular matrix.
 * 
 *  REQUIRES: X is already resized to proper dimensions. */
template <class tU, class tX, class tY,
    typename std::enable_if<internal::can_backward_sub<tU, tX, tY>::value, size_t>::type = 0>
constexpr int backward_sub(internal::Base<tU> const &U, internal::Base<tX> &X,
    internal::Base<tY> const &Y);

/** @fn backward_sub
 *  @param[in] U n by n upper-right triangular matrix.
 *  @param[out] X n by m matrix storing the solution (can be a vector).
 *  @param[in] Y n by m matrix (can be a vector).
 * 
 *  Solves the following linear system of equations U * X = Y where U and Y are
 *  given and U is knows to be an upper triangular matrix.
 * 
 *  Will resize X is required. */
template <class tU, class tX, class tY,
    typename std::enable_if<internal::can_backward_sub<tU, tX, tY>::value, size_t>::type = 0>
constexpr int backward_sub(internal::Base<tU> const &U, internal::Tensor<tX> &X,
    internal::Base<tY> const &Y);

}  // namespace lin

#include "inl/backward_sub.inl"

#endif
