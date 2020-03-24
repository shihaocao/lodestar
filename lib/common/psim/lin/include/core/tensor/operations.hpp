// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_TENSOR_OPERATIONS_HPP_
#define LIN_INCLUDE_CORE_TENSOR_OPERATIONS_HPP_

#include "stream.hpp"
#include "traits.hpp"

#include <cassert>
#include <type_traits>

namespace lin
{
namespace internal
{

template <class tA, class tB>
class Add : public Stream<Add<tA, tB>>
{
 public:
  typedef traits<Add<tA, tB>> Traits;
  constexpr Add() = delete;
  constexpr Add(Stream<tA> const &A, Stream<tB> const &B);
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;

 private:
  Stream<tA> const &A;
  Stream<tB> const &B;
};

template <class tA, class tB>
struct can_add : public are_traits_equal<tA, tB> { };

template <class tA, class tB>
struct elem<Add<tA, tB>> : public elem<tA> { };

template <class tA, class tB>
struct dims<Add<tA, tB>, typename std::enable_if<can_add<tA, tB>::value>::type>
: public dims<tA> { };

template <class tA, class tB>
class Subtract : public Stream<Subtract<tA, tB>>
{
 public:
  typedef traits<Subtract<tA, tB>> Traits;
  constexpr Subtract() = delete;
  constexpr Subtract(Stream<tA> const &A, Stream<tB> const &B);
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;

 private:
  Stream<tA> const &A;
  Stream<tB> const &B;
};

template <class tA, class tB>
struct can_subtract : public are_traits_equal<tA, tB> { };

template <class tA, class tB>
struct elem<Subtract<tA, tB>> : public elem<tA> { };

template <class tA, class tB>
struct dims<Subtract<tA, tB>, typename std::enable_if<can_subtract<tA, tB>::value>::type>
: public dims<tA> { };

template <class tA>
class ScaleMultiple : public Stream<ScaleMultiple<tA>>
{
 public:
  typedef traits<ScaleMultiple<tA>> Traits;
  constexpr ScaleMultiple() = delete;
  constexpr ScaleMultiple(Stream<tA> const &A, typename Traits::elem s);
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;

 private:
  Stream<tA> const &A;
  typename Traits::elem const s;
};

template <class tA>
struct can_scale_multiple : public std::true_type { };

template <class tA>
struct elem<ScaleMultiple<tA>> : public elem<tA> { };

template <class tA>
struct dims<ScaleMultiple<tA>, typename std::enable_if<can_scale_multiple<tA>::value>::type>
: public dims<tA> { };

template <class tA>
class ScaleDivide : public Stream<ScaleDivide<tA>>
{
 public:
  typedef traits<ScaleDivide<tA>> Traits;
  constexpr ScaleDivide() = delete;
  constexpr ScaleDivide(Stream<tA> const &A, typename Traits::elem s);
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;

 private:
  Stream<tA> const &A;
  typename Traits::elem const s;
};

template <class tA>
struct can_scale_divide : public std::true_type { };

template <class tA>
struct elem<ScaleDivide<tA>> : public elem<tA> { };

template <class tA>
struct dims<ScaleDivide<tA>, typename std::enable_if<can_scale_divide<tA>::value>::type>
: public dims<tA> { };

template <class tA, class tB>
class Multiply : public Stream<Multiply<tA, tB>>
{
 public:
  typedef traits<Multiply<tA, tB>> Traits;
  constexpr Multiply() = delete;
  constexpr Multiply(Stream<tA> const &A, Stream<tB> const &B);
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;

 private:
  Stream<tA> const &A;
  Stream<tB> const &B;
};

template <class tA, class tB>
struct can_multiply
: public std::integral_constant<bool, (
    (dims<tA>::cols == dims<tB>::rows) &&
    (dims<tA>::max_cols == dims<tB>::max_rows) &&
    are_elem_equal<tA, tB>::value
  )> { };

template <class tA, class tB>
struct elem<Multiply<tA, tB>> : public elem<tA> { };

template <class tA, class tB>
struct dims<Multiply<tA, tB>, typename std::enable_if<can_multiply<tA, tB>::value>::type>
{
  enum {
    rows = dims<tA>::rows,
    cols = dims<tB>::cols,
    max_rows = dims<tA>::max_rows,
    max_cols = dims<tB>::max_cols
  };
};

template <class tA>
class Transpose : public Stream<Transpose<tA>>
{
 public:
  typedef traits<Transpose<tA>> Traits;
  constexpr Transpose() = delete;
  constexpr Transpose(Stream<tA> const &A);
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;

 private:
  Stream<tA> const &A;
};

template <class tA>
struct can_transpose : public std::true_type { };

template <class tA>
struct elem<Transpose<tA>> : public elem<tA> { };

template <class tA>
struct dims<Transpose<tA>, typename std::enable_if<can_transpose<tA>::value>::type>
{
  enum {
    rows = dims<tA>::cols,
    cols = dims<tA>::rows,
    max_rows = dims<tA>::max_cols,
    max_cols = dims<tA>::max_rows
  };
};

template <class tA, class tB,
    typename std::enable_if<can_add<tA, tB>::value, size_t>::type = 0>
constexpr Add<tA, tB> operator+(Stream<tA> const &A, Stream<tB> const &B);

template <class tA, class tB,
    typename std::enable_if<can_subtract<tA, tB>::value, size_t>::type = 0>
constexpr Subtract<tA, tB> operator-(Stream<tA> const &A, Stream<tB> const &B);

template <class tA,
    typename std::enable_if<can_scale_multiple<tA>::value, size_t>::type = 0>
constexpr ScaleMultiple<tA> operator*(Stream<tA> const &A, typename Stream<tA>::Traits::elem s);

template <class tA,
    typename std::enable_if<can_scale_multiple<tA>::value, size_t>::type = 0>
constexpr ScaleMultiple<tA> operator*(typename Stream<tA>::Traits::elem s, Stream<tA> const &A);

template <class tA,
    typename std::enable_if<can_scale_divide<tA>::value, size_t>::type = 0>
constexpr ScaleDivide<tA> operator/(Stream<tA> const &A, typename Stream<tA>::Traits::elem s);

template <class tA, class tB,
    typename std::enable_if<can_multiply<tA, tB>::value, size_t>::type = 0>
constexpr Multiply<tA, tB> operator*(Stream<tA> const &A, Stream<tB> const &B);

}  // namespace internal

template <class tA,
    typename std::enable_if<internal::can_transpose<tA>::value, size_t>::type = 0>
constexpr internal::Transpose<tA> transpose(internal::Stream<tA> const &A);

template <class tA>
constexpr typename internal::Stream<tA>::Traits::elem fro(internal::Stream<tA> const &A);

}  // namespace lin

#include "inl/operations.inl"

#endif
