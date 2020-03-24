// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_VECTOR_VECTOR_HPP_
#define LIN_INCLUDE_CORE_VECTOR_VECTOR_HPP_

#include "traits.hpp"
#include "../tensor/tensor.hpp"
#include "../tensor/traits.hpp"

#include <type_traits>

namespace lin
{

template <typename tT, size_t tN, size_t tMN = tN>
class RowVector : public internal::Tensor<RowVector<tT, tN, tMN>>
{
  static_assert(internal::is_row_vector<RowVector<tT, tN, tMN>>::value,
      "Invalid RowVector<...> template parameters.");

 public:
  typedef internal::traits<RowVector<tT, tN, tMN>> Traits;
  using internal::Tensor<RowVector<tT, tN, tMN>>::resize;
  using internal::Tensor<RowVector<tT, tN, tMN>>::operator=;
  constexpr RowVector() = default;
  constexpr RowVector(size_t n);
  constexpr RowVector(size_t r, size_t c);
  constexpr RowVector(std::initializer_list<typename Traits::elem> const &l);
  constexpr RowVector(size_t n, std::initializer_list<typename Traits::elem> const &l);
  constexpr RowVector(size_t r, size_t c, std::initializer_list<typename Traits::elem> const &l);
  template <class tE>
  constexpr RowVector(internal::Stream<tE> const &E);
  constexpr void resize(size_t n);
};

template <size_t tN, size_t tMN = tN>
using RowVectorf = RowVector<float, tN, tMN>;

typedef RowVectorf<2> RowVector2f;
typedef RowVectorf<3> RowVector3f;
typedef RowVectorf<4> RowVector4f;

template <size_t tN, size_t tMN = tN>
using RowVectord = RowVector<double, tN, tMN>;

typedef RowVectord<2> RowVector2d;
typedef RowVectord<3> RowVector3d;
typedef RowVectord<4> RowVector4d;

template <typename tT, size_t tN, size_t tMN = tN>
class Vector : public internal::Tensor<Vector<tT, tN, tMN>>
{
  static_assert(internal::is_col_vector<Vector<tT, tN, tMN>>::value,
      "Invalid Vector<...> template parameters.");

 public:
  typedef internal::traits<Vector<tT, tN, tMN>> Traits;
  using internal::Tensor<Vector<tT, tN, tMN>>::resize;
  using internal::Tensor<Vector<tT, tN, tMN>>::operator=;
  constexpr Vector() = default;
  constexpr Vector(size_t n);
  constexpr Vector(size_t r, size_t c);
  constexpr Vector(std::initializer_list<typename Traits::elem> const &l);
  constexpr Vector(size_t n, std::initializer_list<typename Traits::elem> const &l);
  constexpr Vector(size_t r, size_t c, std::initializer_list<typename Traits::elem> const &l);
  template <class tE>
  constexpr Vector(internal::Stream<tE> const &E);
  constexpr void resize(size_t n);
};

template <size_t tN, size_t tMN = tN>
using Vectorf = Vector<float, tN, tMN>;

typedef Vectorf<2> Vector2f;
typedef Vectorf<3> Vector3f;
typedef Vectorf<4> Vector4f;

template <size_t tN, size_t tMN = tN>
using Vectord = Vector<double, tN, tMN>;

typedef Vectord<2> Vector2d;
typedef Vectord<3> Vector3d;
typedef Vectord<4> Vector4d;

namespace internal
{

template <typename tT, size_t tN, size_t tMN>
struct elem<RowVector<tT, tN, tMN>>
{
  typedef tT type;
};

template <typename tT, size_t tN, size_t tMN>
struct dims<RowVector<tT, tN, tMN>>
{
  enum {
    rows = 1,
    cols = tN,
    max_rows = 1,
    max_cols = tMN
  };
};

template <class tA>
struct eval<tA, typename std::enable_if<is_row_vector<tA>::value>::type>
{
  typedef RowVector<
      typename elem<tA>::type,
      dims<tA>::cols,
      dims<tA>::max_cols
    > type;
};

template <typename tT, size_t tN, size_t tMN>
struct elem<Vector<tT, tN, tMN>>
{
  typedef tT type;
};

template <typename tT, size_t tN, size_t tMN>
struct dims<Vector<tT, tN, tMN>>
{
  enum {
    rows = tN,
    cols = 1,
    max_rows = tMN,
    max_cols = 1
  };
};

template <class tA>
struct eval<tA, typename std::enable_if<is_col_vector<tA>::value>::type>
{
  typedef Vector<
      typename elem<tA>::type,
      dims<tA>::rows,
      dims<tA>::max_rows
    > type;
};
}  // namespace internal
}  // namespace lin

#include "inl/vector.inl"

#endif
