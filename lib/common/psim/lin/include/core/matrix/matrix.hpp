// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_MATRIX_MATRIX_HPP_
#define LIN_INCLUDE_CORE_MATRIX_MATRIX_HPP_

#include "traits.hpp"
#include "../tensor/tensor.hpp"
#include "../tensor/traits.hpp"

#include <type_traits>

namespace lin
{

template <typename tT, size_t tR, size_t tC, size_t tMR = tR, size_t tMC = tC>
class Matrix : public internal::Tensor<Matrix<tT, tR, tC, tMR, tMC>>
{
  static_assert(internal::is_matrix<Matrix<tT, tR, tC, tMR, tMC>>::value,
      "Invalid Matrix<...> template parameters.");

 public:
  typedef internal::traits<Matrix<tT, tR, tC, tMR, tMC>> Traits;
  using internal::Tensor<Matrix<tT, tR, tC, tMR, tMC>>::resize;
  using internal::Tensor<Matrix<tT, tR, tC, tMR, tMC>>::operator=;
  constexpr Matrix() = default;
  constexpr Matrix(size_t r, size_t c);
  constexpr Matrix(std::initializer_list<typename Traits::elem> const &l);
  constexpr Matrix(size_t r, size_t c, std::initializer_list<typename Traits::elem> const &l);
  template <class tE>
  constexpr Matrix(internal::Stream<tE> const &E);
};

template <size_t tR, size_t tC, size_t tMR = tR, size_t tMC = tC>
using Matrixf = Matrix<float, tR, tC, tMR, tMC>;

typedef Matrixf<2, 2> Matrix2x2f;
typedef Matrixf<3, 2> Matrix3x2f;
typedef Matrixf<4, 2> Matrix4x2f;
typedef Matrixf<2, 3> Matrix2x3f;
typedef Matrixf<3, 3> Matrix3x3f;
typedef Matrixf<4, 3> Matrix4x3f;
typedef Matrixf<2, 4> Matrix2x4f;
typedef Matrixf<3, 4> Matrix3x4f;
typedef Matrixf<4, 4> Matrix4x4f;

template <size_t tR, size_t tC, size_t tMR = tR, size_t tMC = tC>
using Matrixd = Matrix<double, tR, tC, tMR, tMC>;

typedef Matrixd<2, 2> Matrix2x2d;
typedef Matrixd<3, 2> Matrix3x2d;
typedef Matrixd<4, 2> Matrix4x2d;
typedef Matrixd<2, 3> Matrix2x3d;
typedef Matrixd<3, 3> Matrix3x3d;
typedef Matrixd<4, 3> Matrix4x3d;
typedef Matrixd<2, 4> Matrix2x4d;
typedef Matrixd<3, 4> Matrix3x4d;
typedef Matrixd<4, 4> Matrix4x4d;

namespace internal
{

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
struct elem<Matrix<tT, tR, tC, tMR, tMC>>
{
  typedef tT type;
};

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
struct dims<Matrix<tT, tR, tC, tMR, tMC>>
{
  enum {
    rows = tR,
    cols = tC,
    max_rows = tMR,
    max_cols = tMC
  };
};

template <class tA>
struct eval<tA, typename std::enable_if<is_matrix<tA>::value>::type>
{
  typedef Matrix<
      typename elem<tA>::type,
      dims<tA>::rows,
      dims<tA>::cols,
      dims<tA>::max_rows,
      dims<tA>::max_cols
    > type;
};
}  // namespace internal
}  // namespace lin

#include "inl/matrix.inl"

#endif
