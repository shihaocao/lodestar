// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../backward_sub.hpp"

namespace lin
{

template <class tU, class tX, class tY,
    typename std::enable_if<internal::can_backward_sub<tU, tX, tY>::value, size_t>::type>
constexpr int backward_sub(internal::Base<tU> const &U, internal::Base<tX> &X,
    internal::Base<tY> const &Y)
{
  typedef internal::traits<tU> TU;
  typedef internal::traits<tY> TY;

  assert(U.rows() == U.cols() /* U isn't square in backward_sub(...) */);
  assert(U.cols() == Y.rows() /* Y rows don't match in backward_sub(...) */);
  assert(Y.rows() == X.rows() /* X rows don't match in backward_sub(...) */);
  assert(Y.cols() == X.cols() /* X cols don't match in backward_sub(...) */);

  // Solve for the last rows
  // It's trivially the last row of Y divided by the bottom right element of U
  const size_t m = U.rows() - 1;
  ref_row(X, m) = ref_row(Y, m) / U(m, m);

  // Solve for the other rows in descending order
  for (size_t n = m - 1;; n--) {
    ref_row(X, n) = (
            ref_row(Y, n) - (ref<1, 0, 1, TU::max_rows>(U, n, n + 1, 1, m - n) * 
                ref<0, TY::cols, TY::max_rows, TY::max_cols>(X, n + 1, 0, m - n, X.cols()))
        ) / U(n, n);
    if (n == 0) break;  // Must perform this check here for unsigned value
  }

  return 0;  // TODO : Return an actual error code
}

template <class tU, class tX, class tY,
    typename std::enable_if<internal::can_backward_sub<tU, tX, tY>::value, size_t>::type>
constexpr int backward_sub(internal::Base<tU> const &U, internal::Tensor<tX> &X,
    internal::Base<tY> const &Y)
{
  X.resize(Y.rows(), Y.cols());
  return backward_sub(U, static_cast<internal::Base<tX> &>(X), Y);
}
}  // namespace lin
