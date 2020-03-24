// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../operations.hpp"

namespace lin
{

template <class tA, class tB,
    typename std::enable_if<internal::are_vector_traits_equal<tA, tB>::value, size_t>::type>
constexpr typename internal::elem<tA>::type dot(internal::Stream<tA> const &A,
    internal::Stream<tB> const &B)
{
  assert(A.size() == B.size() /* Incompatible size in dot(...) */);
  typename internal::elem<tA>::type x = A(0) * B(0);
  for (size_t i = 1; i < A.size(); i++) x += A(i) * B(i);
  return x;
}

template <class tA,
    typename std::enable_if<internal::is_vector<tA>::value, size_t>::type>
constexpr typename internal::elem<tA>::type norm(internal::Stream<tA> const &A)
{
  return std::sqrt(fro(A));
}

template <class tA, class tB,
    typename std::enable_if<internal::can_cross<tA, tB>::value, size_t>::type>
constexpr typename internal::eval<tA>::type cross(internal::Stream<tA> const &A,
    internal::Stream<tB> const &B)
{
  return typename internal::eval<tA>::type({
    A(1) * B(2) - A(2) * B(1),
    A(2) * B(0) - A(0) * B(2),
    A(0) * B(1) - A(1) * B(0)
  });
}
}  // namespace lin
