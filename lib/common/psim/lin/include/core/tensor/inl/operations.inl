// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../operations.hpp"

namespace lin
{
namespace internal
{

template <class tA, class tB>
constexpr Add<tA, tB>::Add(Stream<tA> const &A, Stream<tB> const &B)
: A(A), B(B)
{
  assert(A.rows() == B.rows() /* Invalid rows in Add<...>::Add */);
  assert(A.cols() == B.cols() /* Invalid cols in Add<...>::Add */);
}

template <class tA, class tB>
constexpr size_t Add<tA, tB>::rows() const
{
  return A.rows();
}

template <class tA, class tB>
constexpr size_t Add<tA, tB>::cols() const
{
  return A.cols();
}

template <class tA, class tB>
constexpr typename Add<tA, tB>::Traits::elem
Add<tA, tB>::operator()(size_t i, size_t j) const
{
  return A(i, j) + B(i, j);
}

template <class tA, class tB>
constexpr typename Add<tA, tB>::Traits::elem
Add<tA, tB>::operator()(size_t i) const
{
  return A(i) + B(i);
}

template <class tA, class tB>
constexpr Subtract<tA, tB>::Subtract(Stream<tA> const &A, Stream<tB> const &B)
: A(A), B(B)
{
  assert(A.rows() == B.rows() /* Invalid rows in Subtract<...>::Subtract */);
  assert(A.cols() == B.cols() /* Invalid cols in Subtract<...>::Subtract */);
}

template <class tA, class tB>
constexpr size_t Subtract<tA, tB>::rows() const
{
  return A.rows();
}

template <class tA, class tB>
constexpr size_t Subtract<tA, tB>::cols() const
{
  return A.cols();
}

template <class tA, class tB>
constexpr typename Subtract<tA, tB>::Traits::elem
Subtract<tA, tB>::operator()(size_t i, size_t j) const
{
  return A(i, j) - B(i, j);
}

template <class tA, class tB>
constexpr typename Subtract<tA, tB>::Traits::elem
Subtract<tA, tB>::operator()(size_t i) const
{
  return A(i) - B(i);
}

template <class tA>
constexpr ScaleMultiple<tA>::ScaleMultiple(Stream<tA> const &A, typename Traits::elem s)
: A(A), s(s) { }

template <class tA>
constexpr size_t ScaleMultiple<tA>::rows() const
{
  return A.rows();
}

template <class tA>
constexpr size_t ScaleMultiple<tA>::cols() const
{
  return A.cols();
}

template <class tA>
constexpr typename ScaleMultiple<tA>::Traits::elem
ScaleMultiple<tA>::operator()(size_t i, size_t j) const
{
  return A(i, j) * s;
}

template <class tA>
constexpr typename ScaleMultiple<tA>::Traits::elem
ScaleMultiple<tA>::operator()(size_t i) const
{
  return A(i) * s;
}

template <class tA>
constexpr ScaleDivide<tA>::ScaleDivide(Stream<tA> const &A, typename Traits::elem s)
: A(A), s(s) { }

template <class tA>
constexpr size_t ScaleDivide<tA>::rows() const
{
  return A.rows();
}

template <class tA>
constexpr size_t ScaleDivide<tA>::cols() const
{
  return A.cols();
}

template <class tA>
constexpr typename ScaleDivide<tA>::Traits::elem
ScaleDivide<tA>::operator()(size_t i, size_t j) const
{
  return A(i, j) / s;
}

template <class tA>
constexpr typename ScaleDivide<tA>::Traits::elem
ScaleDivide<tA>::operator()(size_t i) const
{
  return A(i) / s;
}

template <class tA, class tB>
constexpr Multiply<tA, tB>::Multiply(Stream<tA> const &A, Stream<tB> const &B)
: A(A), B(B)
{
  assert(A.cols() == B.rows() /* Incompatiblity in Multiply<...>::Multiply */);
}

template <class tA, class tB>
constexpr size_t Multiply<tA, tB>::rows() const
{
  return A.rows();
}

template <class tA, class tB>
constexpr size_t Multiply<tA, tB>::cols() const
{
  return B.cols();
}

template <class tA, class tB>
constexpr typename Multiply<tA, tB>::Traits::elem
Multiply<tA, tB>::operator()(size_t i, size_t j) const
{
  typename Traits::elem x = A(i, 0) * B(0, j);
  for (size_t k = 1; k < A.cols(); k++) x += A(i, k) * B(k, j);
  return x;
}

template <class tA, class tB>
constexpr typename Multiply<tA, tB>::Traits::elem
Multiply<tA, tB>::operator()(size_t i) const
{
  return operator()(i / cols(), i % cols());
}

template <class tA>
constexpr Transpose<tA>::Transpose(Stream<tA> const &A)
: A(A) { }

template <class tA>
constexpr size_t Transpose<tA>::rows() const
{
  return A.cols();
}

template <class tA>
constexpr size_t Transpose<tA>::cols() const
{
  return A.rows();
}

template <class tA>
constexpr typename Transpose<tA>::Traits::elem
Transpose<tA>::operator()(size_t i, size_t j) const
{
  return A(j, i);
}

template <class tA>
constexpr typename Transpose<tA>::Traits::elem
Transpose<tA>::operator()(size_t i) const
{
  return operator()(i / cols(), i % cols());
}

template <class tA, class tB,
    typename std::enable_if<can_add<tA, tB>::value, size_t>::type>
constexpr Add<tA, tB> operator+(Stream<tA> const &A, Stream<tB> const &B)
{
  return Add<tA, tB>(A, B);
}

template <class tA, class tB,
    typename std::enable_if<can_subtract<tA, tB>::value, size_t>::type>
constexpr Subtract<tA, tB> operator-(Stream<tA> const &A, Stream<tB> const &B)
{
  return Subtract<tA, tB>(A, B);
}

template <class tA,
    typename std::enable_if<can_scale_multiple<tA>::value, size_t>::type>
constexpr ScaleMultiple<tA> operator*(Stream<tA> const &A, typename Stream<tA>::Traits::elem s)
{
  return ScaleMultiple<tA>(A, s);
}

template <class tA,
    typename std::enable_if<can_scale_multiple<tA>::value, size_t>::type>
constexpr ScaleMultiple<tA> operator*(typename Stream<tA>::Traits::elem s, Stream<tA> const &A)
{
  return (A * s);
}

template <class tA,
    typename std::enable_if<can_scale_divide<tA>::value, size_t>::type>
constexpr ScaleDivide<tA> operator/(Stream<tA> const &A, typename Stream<tA>::Traits::elem s)
{
  return ScaleDivide<tA>(A, s);
}

template <class tA, class tB,
    typename std::enable_if<can_multiply<tA, tB>::value, size_t>::type>
constexpr Multiply<tA, tB> operator*(Stream<tA> const &A, Stream<tB> const &B)
{
  return Multiply<tA, tB>(A, B);
}
}  // namespace internal

template <class tA,
    typename std::enable_if<internal::can_transpose<tA>::value, size_t>::type>
constexpr internal::Transpose<tA> transpose(internal::Stream<tA> const &A)
{
  return internal::Transpose<tA>(A);
}

template <class tA>
constexpr typename internal::Stream<tA>::Traits::elem fro(internal::Stream<tA> const &A)
{
  typename internal::Stream<tA>::Traits::elem x = A(0) * A(0);
  for (size_t i = 1; i < A.size(); i++) x += A(i) * A(i);
  return x;
}
}  // namespace lin
