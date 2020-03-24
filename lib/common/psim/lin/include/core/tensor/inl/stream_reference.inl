// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../stream_reference.hpp"

namespace lin
{
namespace internal
{

template <size_t tR, size_t tC, size_t tMR, size_t tMC, class tE>
constexpr StreamReference<tR, tC, tMR, tMC, tE>::StreamReference(
    Stream<tE> const &E, size_t i, size_t j, size_t r, size_t c)
: E(E), i(i), j(j)
{
  assert(i + r <= E.rows() /* Invalid dimension in StreamReference<...>::StreamReference */);
  assert(j + c <= E.cols() /* Invalid dimension in StreamReference<...>::StreamReference */);
  resize(r, c);
}

template <size_t tR, size_t tC, size_t tMR, size_t tMC, class tE>
constexpr typename StreamReference<tR, tC, tMR, tMC, tE>::Traits::elem
StreamReference<tR, tC, tMR, tMC, tE>::operator()(size_t i, size_t j) const
{
  assert(i < rows() /* Invalid row index in StreamReference<...>::operator() */);
  assert(j < cols() /* Invalid col index in StreamReference<...>::operator() */);
  return E(this->i + i, this->j + j);
}

template <size_t tR, size_t tC, size_t tMR, size_t tMC, class tE>
constexpr typename StreamReference<tR, tC, tMR, tMC, tE>::Traits::elem
StreamReference<tR, tC, tMR, tMC, tE>::operator()(size_t i) const
{
  return operator()(i / cols(), i % cols());
}
}  // namespace internal

template <size_t tR, size_t tC, size_t tMR, size_t tMC, class tE>
constexpr internal::StreamReference<tR, tC, tMR, tMC, tE> const
ref(internal::Stream<tE> const &E, size_t i, size_t j, size_t r, size_t c)
{
  return internal::StreamReference<tR, tC, tMR, tMC, tE>(E, i, j, r, c);
}

template <size_t tR, size_t tC, class tE>
constexpr internal::StreamReference<tR, tC, tR, tC, tE> const
ref(internal::Stream<tE> const &E, size_t i, size_t j)
{
  return ref<tR, tC, tR, tC>(E, i, j);
}

template <class tE>
constexpr auto ref_row(internal::Stream<tE> const &E, size_t i)
{
  typedef internal::traits<tE> TE;
  return ref<1, TE::cols, 1, TE::max_cols>(E, i, 0, 1, E.cols());
}

template <class tE>
constexpr auto ref_col(internal::Stream<tE> const &E, size_t j)
{
  typedef internal::traits<tE> TE;
  return ref<TE::rows, 1, TE::max_rows, 1>(E, 0, j, E.rows(), 1);
}
}  // namespace lin
