// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../base_reference.hpp"

namespace lin
{
namespace internal
{

template <size_t tR, size_t tC, size_t tMR, size_t tMC, class tE>
constexpr BaseReference<tR, tC, tMR, tMC, tE>::BaseReference(Base<tE> &E,
    size_t i, size_t j, size_t r, size_t c)
: E(E), i(i), j(j)
{
  assert(i + r <= E.rows() /* Invalid dimension in BaseReference<...>::BaseReference */);
  assert(j + c <= E.cols() /* Invalid dimension in BaseReference<...>::BaseReference */);
  resize(r, c);
}

template <size_t tR, size_t tC, size_t tMR, size_t tMC, class tE>
constexpr typename BaseReference<tR, tC, tMR, tMC, tE>::Traits::elem &
BaseReference<tR, tC, tMR, tMC, tE>::operator()(size_t i, size_t j)
{
  assert(i < rows() /* Invalid row index in BaseReference<...>::operator() */);
  assert(j < cols() /* Invalid col index in BaseReference<...>::operator() */);
  return E(this->i + i, this->j + j);
}

template <size_t tR, size_t tC, size_t tMR, size_t tMC, class tE>
constexpr typename BaseReference<tR, tC, tMR, tMC, tE>::Traits::elem &
BaseReference<tR, tC, tMR, tMC, tE>::operator()(size_t i)
{
  return operator()(i / cols(), i % cols());
}
}  // namespace internal

template <size_t tR, size_t tC, size_t tMR, size_t tMC, class tE>
constexpr internal::BaseReference<tR, tC, tMR, tMC, tE>
ref(internal::Base<tE> &E, size_t i, size_t j, size_t r, size_t c)
{
  return internal::BaseReference<tR, tC, tMR, tMC, tE>(E, i, j, r, c);
}

template <size_t tR, size_t tC, class tE>
constexpr internal::BaseReference<tR, tC, tR, tC, tE>
ref(internal::Base<tE> &E, size_t i, size_t j)
{
  return ref<tR, tC, tR, tC>(E, i, j);
}

template <class tE>
constexpr auto ref_row(internal::Base<tE> &E, size_t i)
{
  typedef internal::traits<tE> TE;
  return ref<1, TE::cols, 1, TE::max_cols>(E, i, 0, 1, E.cols());
}

template <class tE>
constexpr auto ref_col(internal::Base<tE> &E, size_t j)
{
  typedef internal::traits<tE> TE;
  return ref<TE::rows, 1, TE::max_rows, 1>(E, 0, j, E.rows(), 1);
}
}  // namespace lin
