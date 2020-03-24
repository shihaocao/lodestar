// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_TENSOR_GENERATORS_HPP_
#define LIN_INCLUDE_CORE_TENSOR_GENERATORS_HPP_

#include "dimensions.hpp"
#include "stream.hpp"
#include "traits.hpp"

#include <cassert>
#include <limits>

#if defined(LIN_DESKTOP) && !defined(LIN_RANDOM_SEED)
#include <ctime>
#endif

namespace lin
{
namespace internal
{

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
class Constants : public Stream<Constants<tT, tR, tC, tMR, tMC>>,
    public Dimensions<Constants<tT, tR, tC, tMR, tMC>>
{
 public:
  typedef traits<Constants<tT, tR, tC, tMR, tMC>> Traits;
  using Dimensions<Constants<tT, tR, tC, tMR, tMC>>::rows;
  using Dimensions<Constants<tT, tR, tC, tMR, tMC>>::cols;
  using Stream<Constants<tT, tR, tC, tMR, tMC>>::size;
  constexpr Constants() = delete;
  constexpr Constants(tT t, size_t r, size_t c);
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;

 private:
  using Dimensions<Constants<tT, tR, tC, tMR, tMC>>::resize;
  using Stream<Constants<tT, tR, tC, tMR, tMC>>::derived;
  tT const t;
};

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
struct elem<Constants<tT, tR, tC, tMR, tMC>>
{
  typedef tT type;
};

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
struct dims<Constants<tT, tR, tC, tMR, tMC>>
{
  enum {
    rows = tR,
    cols = tC,
    max_rows = tMR,
    max_cols = tMC,
  };
};

class RandomsGenerator {
private:
  mutable long long seed;

public:
  constexpr RandomsGenerator() = delete;
  constexpr RandomsGenerator(unsigned long long seed);
  constexpr double next();
};

#if defined(LIN_DESKTOP) && !defined(LIN_RANDOM_SEED)
static RandomsGenerator rand(time(nullptr));
#else
static RandomsGenerator rand(LIN_RANDOM_SEED);
#endif

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
class Randoms : public Stream<Randoms<tT, tR, tC, tMR, tMC>>,
    public Dimensions<Randoms<tT, tR, tC, tMR, tMC>>
{
 public:
  typedef traits<Randoms<tT, tR, tC, tMR, tMC>> Traits;
  using Dimensions<Randoms<tT, tR, tC, tMR, tMC>>::rows;
  using Dimensions<Randoms<tT, tR, tC, tMR, tMC>>::cols;
  using Stream<Randoms<tT, tR, tC, tMR, tMC>>::size;
  constexpr Randoms() = delete;
  constexpr Randoms(size_t r, size_t c, RandomsGenerator &rand);
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;

 private:
  using Dimensions<Randoms<tT, tR, tC, tMR, tMC>>::resize;
  using Stream<Randoms<tT, tR, tC, tMR, tMC>>::derived;
  RandomsGenerator &rand;
};

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
struct elem<Randoms<tT, tR, tC, tMR, tMC>>
{
  typedef tT type;
};

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
struct dims<Randoms<tT, tR, tC, tMR, tMC>>
{
  enum {
    rows = tR,
    cols = tC,
    max_rows = tMR,
    max_cols = tMC,
  };
};
}  // namespace internal

template <typename tT, size_t tR, size_t tC, size_t tMR = tR, size_t tMC = tC>
constexpr internal::Constants<tT, tR, tC, tMR, tMC>
consts(tT t, size_t r = tMR, size_t c = tMC);

template <class tA>
constexpr auto consts(typename internal::elem<tA>::type t, size_t r = internal::dims<tA>::max_rows,
    size_t c = internal::dims<tA>::max_cols);

template <typename tT, size_t tR, size_t tC, size_t tMR = tR, size_t tMC = tC>
constexpr internal::Constants<tT, tR, tC, tMR, tMC>
zeros(size_t r = tMR, size_t c = tMC);

template <class tA>
constexpr auto zeros(size_t r = internal::dims<tA>::max_rows,
    size_t c = internal::dims<tA>::max_cols);

template <typename tT, size_t tR, size_t tC, size_t tMR = tR, size_t tMC = tC>
constexpr internal::Constants<tT, tR, tC, tMR, tMC>
ones(size_t r = tMR, size_t c = tMC);

template <class tA>
constexpr auto ones(size_t r = internal::dims<tA>::max_rows,
    size_t c = internal::dims<tA>::max_cols);

template <typename tT, size_t tR, size_t tC, size_t tMR = tR, size_t tMC = tC>
constexpr internal::Constants<tT, tR, tC, tMR, tMC>
nans(size_t r = tMR, size_t c = tMC);

template <class tA>
constexpr auto nans(size_t r = internal::dims<tA>::max_rows,
    size_t c = internal::dims<tA>::max_cols);

template <typename tT, size_t tR, size_t tC, size_t tMR = tR, size_t tMC = tC>
constexpr internal::Randoms<tT, tR, tC, tMR, tMC>
rands(size_t r = tMR, size_t c = tMC, internal::RandomsGenerator &rand = internal::rand);

template <class tA>
constexpr auto rands(size_t r = internal::dims<tA>::max_rows,
    size_t c = internal::dims<tA>::max_cols, internal::RandomsGenerator &rand = internal::rand);

}  // namespace lin

#include "inl/generators.inl"

#endif
