// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_ALGORITHMS_QR_HPP_
#define LIN_INCLUDE_ALGORITHMS_QR_HPP_

#include "../core/core.hpp"

#include <cassert>
#include <type_traits>

namespace lin
{
namespace internal
{

/** @struct can_qr
 *  True if the qr factorization function can be called on the specified
 *  template and false otherwise. To be compatible, tM and tQ must have
 *  identical traits. Furthermore, the product of tQ and tR must exist and
 *  result in traits identical to tM - i.e. because M = Q * R. */
template <class tM, class tQ, class tR>
struct can_qr : public std::integral_constant<bool, (
    are_traits_equal<tM, tQ>::value && are_traits_equal<tM, Multiply<tQ, tR>>::value
  )> { };

}  // namespace internal

/** @fn qr
 *  @param[in] M m by n matrix where m >= n.
 *  @param[out] Q Orthonormal m by n matrix where m >= n.
 *  @param[out] R Upper triangular n by n matrix.
 * 
 *  Calculates the QR factorization of M and stores the result in Q and R.
 * 
 *  REQUIRES: Q and R are already sized to the proper dimensions. */
template <class tM, class tQ, class tR,
    typename std::enable_if<internal::can_qr<tM, tQ, tR>::value, size_t>::type = 0>
constexpr int qr(internal::Stream<tM> const &M, internal::Base<tQ> &Q, internal::Base<tR> &R);

/** @fn qr
 *  @param[in] M m by n matrix where m >= n.
 *  @param[out] Q Orthonormal m by n matrix where m >= n.
 *  @param[out] R Upper triangular n by n matrix.
 * 
 *  Calculates the QR factorization of M and stores the result in Q and R.
 * 
 *  Will resize Q and R if required. */
template <class tM, class tQ, class tR,
    typename std::enable_if<internal::can_qr<tM, tQ, tR>::value, size_t>::type = 0>
constexpr int qr(internal::Stream<tM> const &M, internal::Tensor<tQ> &Q, internal::Tensor<tR> &R);

}  // namespace lin

#include "inl/qr.inl"

#endif
