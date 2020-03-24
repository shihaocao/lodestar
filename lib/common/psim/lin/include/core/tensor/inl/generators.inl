// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../generators.hpp"

namespace lin
{

namespace internal
{

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
constexpr Constants<tT, tR, tC, tMR, tMC>::Constants(tT t, size_t r, size_t c)
: t(t)
{
  resize(r, c);
}

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
constexpr typename Constants<tT, tR, tC, tMR, tMC>::Traits::elem
Constants<tT, tR, tC, tMR, tMC>::operator()(size_t i, size_t j) const
{
  assert(i < rows() /* Invalid row index in Constants<...>::operator() */);
  assert(j < cols() /* Invalid col index in Constants<...>::operator() */);
  return t;
}

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
constexpr typename Constants<tT, tR, tC, tMR, tMC>::Traits::elem
Constants<tT, tR, tC, tMR, tMC>::operator()(size_t i) const
{
  assert(i < size() /* Invalid size index in Constants<...>::operator() */);
  return t;
}

constexpr RandomsGenerator::RandomsGenerator(unsigned long long seed)
: seed(seed ^ 4101842887655102017LL)
{
  next();
}

constexpr double RandomsGenerator::next()
{
  seed ^= (seed >> 21);
  seed ^= (seed << 35);
  seed ^= (seed >> 4);
  return 5.42101086242752217E-20 * (seed * 2685821657736338717ULL);
}

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
constexpr Randoms<tT, tR, tC, tMR, tMC>::Randoms(size_t r, size_t c, RandomsGenerator &rand)
: rand(rand)
{
  resize(r, c);
}

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
constexpr typename Randoms<tT, tR, tC, tMR, tMC>::Traits::elem
Randoms<tT, tR, tC, tMR, tMC>::operator()(size_t i, size_t j) const
{
  assert(i < rows() /* Invalid row index in Constants<...>::operator() */);
  assert(j < cols() /* Invalid col index in Constants<...>::operator() */);
  return rand.next();
}

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
constexpr typename Randoms<tT, tR, tC, tMR, tMC>::Traits::elem
Randoms<tT, tR, tC, tMR, tMC>::operator()(size_t i) const
{
  assert(i < size() /* Invalid size index in Constants<...>::operator() */);
  return rand.next();
}
}  // namespace internal

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
constexpr internal::Constants<tT, tR, tC, tMR, tMC>
consts(tT t, size_t r, size_t c)
{
  return internal::Constants<tT, tR, tC, tMR, tMC>(t, r, c);
}

template <class tA>
constexpr auto consts(typename internal::elem<tA>::type t, size_t r, size_t c)
{
  typedef internal::traits<tA> Traits;
  return consts<typename Traits::elem, Traits::rows, Traits::cols,
      Traits::max_rows, Traits::max_cols>(t, r, c);
}

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
constexpr internal::Constants<tT, tR, tC, tMR, tMC>
zeros(size_t r, size_t c)
{
  return consts<tT, tR, tC, tMR, tMC>(static_cast<tT>(0.0), r, c);
}

template <class tA>
constexpr auto zeros(size_t r, size_t c)
{
  typedef internal::traits<tA> TA;
  return zeros<typename TA::elem, TA::rows, TA::cols, TA::max_rows, TA::max_cols>(r, c);
}

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
constexpr internal::Constants<tT, tR, tC, tMR, tMC>
ones(size_t r, size_t c)
{
  return consts<tT, tR, tC, tMR, tMC>(static_cast<tT>(1.0), r, c);
}

template <class tA>
constexpr auto ones(size_t r, size_t c)
{
  typedef internal::traits<tA> TA;
  return ones<typename TA::elem, TA::rows, TA::cols, TA::max_rows, TA::max_cols>(r, c);
}

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
constexpr internal::Constants<tT, tR, tC, tMR, tMC>
nans(size_t r, size_t c)
{
  static_assert(std::numeric_limits<tT>::has_quiet_NaN, "Quiet NaNs not supported.");
  return consts<tT, tR, tC, tMR, tMC>(std::numeric_limits<tT>::quiet_NaN(), r, c);
}

template <class tA>
constexpr auto nans(size_t r, size_t c)
{
  typedef internal::traits<tA> TA;
  return nans<typename TA::elem, TA::rows, TA::cols, TA::max_rows, TA::max_cols>(r, c);
}

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
constexpr internal::Randoms<tT, tR, tC, tMR, tMC>
rands(size_t r, size_t c, internal::RandomsGenerator &rand)
{
  return internal::Randoms<tT, tR, tC, tMR, tMC>(r, c, rand);
}

template <class tA>
constexpr auto rands(size_t r, size_t c, internal::RandomsGenerator &rand)
{
  typedef internal::traits<tA> TA;
  return rands<typename TA::elem, TA::rows, TA::cols, TA::max_rows, TA::max_cols>(r, c, rand);
}
}  // namespace lin
