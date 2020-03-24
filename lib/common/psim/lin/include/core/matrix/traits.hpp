// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_MATRIX_TRAITS_HPP_
#define LIN_INCLUDE_CORE_MATRIX_TRAITS_HPP_

#include "../tensor/traits.hpp"
#include "../vector/traits.hpp"

#include <type_traits>

namespace lin
{
namespace internal
{

template <class tA>
struct is_matrix : public std::integral_constant<bool, !is_vector<tA>::value> { };

template <class tA>
struct is_tall : public std::integral_constant<bool, (
    (dims<tA>::max_rows >= dims<tA>::max_cols)
  )> { };

template <class tA>
struct is_short : public std::integral_constant<
    bool, (dims<tA>::max_rows <= dims<tA>::max_cols)
  > { };

template <class tA>
struct is_square : public std::integral_constant<bool,
    (dims<tA>::rows == dims<tA>::cols) && (dims<tA>::max_cols == dims<tA>::max_rows)
  > { };

}  // namespace internal
}  // namespace lin

#endif
