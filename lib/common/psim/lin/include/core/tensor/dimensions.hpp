// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_TENSOR_DIMENSIONS_HPP_
#define LIN_INCLUDE_CORE_TENSOR_DIMENSIONS_HPP_

#include "traits.hpp"

#include <cassert>

namespace lin
{
namespace internal
{

template <size_t tN, size_t tMN>
class Dimension;

template <class tD>
class Dimensions
{
 public:
  constexpr Dimensions() = default;
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr void resize(size_t r, size_t c);

 private:
  Dimension<dims<tD>::rows, dims<tD>::max_rows> row_dimension;
  Dimension<dims<tD>::cols, dims<tD>::max_cols> col_dimension;
};
}  // namespace internal
}  // namespace lin

#include "inl/dimensions.inl"

#endif
