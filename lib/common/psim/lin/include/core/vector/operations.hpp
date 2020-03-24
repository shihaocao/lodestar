// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_VECTOR_OPERATIONS_HPP_
#define LIN_INCLUDE_CORE_VECTOR_OPERATIONS_HPP_

#include "../tensor/stream.hpp"
#include "traits.hpp"

#include <cassert>
#include <cmath>  // TODO : Perhaps overkill for embedded systems
#include <type_traits>

namespace lin
{
namespace internal
{

template <class tA, class tB>
struct can_cross
: public std::integral_constant<bool, (
    are_vector_traits_equal<tA, tB>::value && (vector_traits<tA>::size == 3)
  )> { };

}  // namespace internal

template <class tA, class tB,
    typename std::enable_if<internal::are_vector_traits_equal<tA, tB>::value, size_t>::type = 0>
constexpr typename internal::elem<tA>::type dot(internal::Stream<tA> const &A,
    internal::Stream<tB> const &B);

template <class tA,
    typename std::enable_if<internal::is_vector<tA>::value, size_t>::type = 0>
constexpr typename internal::elem<tA>::type norm(internal::Stream<tA> const &A);

template <class tA, class tB,
    typename std::enable_if<internal::can_cross<tA, tB>::value, size_t>::type = 0>
constexpr typename internal::eval<tA>::type cross(internal::Stream<tA> const &A,
    internal::Stream<tB> const &B);

}  // namespace lin

#include "inl/operations.inl"

#endif
