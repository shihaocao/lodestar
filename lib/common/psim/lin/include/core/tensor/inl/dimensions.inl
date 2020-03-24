// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../dimensions.hpp"

namespace lin
{
namespace internal
{

template <size_t tN>
class Dimension<tN, tN>
{
 public:
  constexpr Dimension() = default;
  constexpr size_t get() const { return tN; }
  constexpr void resize(size_t n) {
    assert(n == tN /* Invalid resize in Dimension<tN, tN>::resize */);
  }
};

template <size_t tMN>
class Dimension<0, tMN>
{
 private:
  size_t n = tMN;
 public:
  constexpr Dimension() = default;
  constexpr size_t get() const { return n; }
  constexpr void resize(size_t n) {
    assert(n <= tMN /* Invalid resize in Dimension<0, tMN>::resize */);
    this->n = n;
  }
};

template <class tD>
constexpr size_t Dimensions<tD>::rows() const
{
  return row_dimension.get();
}

template <class tD>
constexpr size_t Dimensions<tD>::cols() const
{
  return col_dimension.get();
}

template <class tD>
constexpr void Dimensions<tD>::resize(size_t r, size_t c)
{
  row_dimension.resize(r);
  col_dimension.resize(c);
}
}  // namespace internal
}  // namespace lin
