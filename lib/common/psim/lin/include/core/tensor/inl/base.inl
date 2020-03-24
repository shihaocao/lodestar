// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../base.hpp"

namespace lin
{
namespace internal
{

template <class tD>
constexpr typename Base<tD>::Traits::elem Base<tD>::operator()(size_t i, size_t j) const
{
  return const_cast<Base<tD> &>(*this)(i, j);
}

template <class tD>
constexpr typename Base<tD>::Traits::elem Base<tD>::operator()(size_t i) const
{
  return const_cast<Base<tD> &>(*this)(i);
}

template <class tD>
constexpr typename Base<tD>::Traits::elem &Base<tD>::operator()(size_t i, size_t j)
{
  return derived()(i, j);
}

template <class tD>
constexpr typename Base<tD>::Traits::elem &Base<tD>::operator()(size_t i)
{
  return derived()(i);
}

template <class tD>
constexpr tD &Base<tD>::operator=(std::initializer_list<typename Base<tD>::Traits::elem> const &l)
{
  assert(size() == l.size() /* Incompatible size in Base<...>::operator= */);
  size_t i = 0;
  auto it = l.begin();
  while (it < l.end()) operator()(i++) = *(it++);
  return derived();
}

template <class tD>
template <class tE, typename std::enable_if<can_assign<tD, tE>::value, size_t>::type>
constexpr tD &Base<tD>::operator=(Stream<tE> const &E)
{
  assert(rows() == E.rows() /* Incompatible rows in Base<...>::operator=<...> */);
  assert(cols() == E.cols() /* Incompatible cols in Base<...>::operator=<...> */);
  for (size_t i = 0; i < size(); i++) operator()(i) = E(i);
  return derived();
}
}  // namespace internal
}  // namespace lin
