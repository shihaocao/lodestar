// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../qr.hpp"

namespace lin
{

template <class tM, class tQ, class tR,
    typename std::enable_if<internal::can_qr<tM, tQ, tR>::value, size_t>::type>
constexpr int qr(internal::Stream<tM> const &M, internal::Base<tQ> &Q, internal::Base<tR> &R)
{
  assert(M.rows() >= M.cols() /* M isn't 'tall' in qr(...) */);
  assert(M.rows() == Q.rows() /* Q rows doesn't match in qr(...) */);
  assert(M.cols() == Q.cols() /* Q cols doesn't match in qr(...) */);
  assert(M.cols() == R.rows() /* R rows doesn't match in qr(...) */);
  assert(M.cols() == R.cols() /* R cols doesn't match in qr(...) */);

  // Initialize R and Q
  R = zeros<tR>(R.rows(), R.cols());
  Q = M;

  for (size_t j = 0; j < M.cols(); j++) {
    auto Qj = ref_col(Q, j);

    // Normalize this column
    R(j, j) = norm(Qj);
    Qj = Qj / R(j, j);

    // Remove parallel components from subsequent columns
    for (size_t k = j + 1; k < M.cols(); k++) {
      auto Qk = ref_col(Q, k);
      R(j, k) = dot(Qj, Qk);
      Qk = Qk - Qj * R(j, k);
    }
  }

  return 0;  // TODO : Return an actual status code
}

template <class tM, class tQ, class tR,
    typename std::enable_if<internal::can_qr<tM, tQ, tR>::value, size_t>::type>
constexpr int qr(internal::Stream<tM> const &M, internal::Tensor<tQ> &Q, internal::Tensor<tR> &R)
{
  // Resize while Q and R and stil Tensor types
  Q.resize(M.rows(), M.cols());
  R.resize(M.cols(), M.cols());
  // Calculate the qr factorization
  return qr(M, static_cast<internal::Base<tQ> &>(Q), static_cast<internal::Base<tR> &>(R));
}
}  // namespace lin
