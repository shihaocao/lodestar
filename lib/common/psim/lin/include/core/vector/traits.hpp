// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_VECTOR_TRAITS_HPP_
#define LIN_INCLUDE_CORE_VECTOR_TRAITS_HPP_

#include "../tensor/traits.hpp"

#include <type_traits>

namespace lin
{
namespace internal
{

template <class tA>
struct is_row_vector : public std::integral_constant<bool, (
    has_fixed_rows<tA>::value && (dims<tA>::rows == 1) && (dims<tA>::max_cols > 1)
  )> { };

template <class tA>
struct is_col_vector : public std::integral_constant<bool, (
    has_fixed_cols<tA>::value && (dims<tA>::cols == 1) && (dims<tA>::max_rows > 1)
  )> { };

template <class tA>
struct is_vector : public std::integral_constant<bool, (
    is_row_vector<tA>::value || is_col_vector<tA>::value
  )> { };

template <class tA, typename tT = void>
struct vector_traits;

template <class tA>
struct vector_traits<tA, typename std::enable_if<is_row_vector<tA>::value>::type>
{
  enum {
    size = traits<tA>::cols,
    max_size = traits<tA>::max_cols
  };
  typedef typename traits<tA>::elem elem;
};

template <class tA>
struct vector_traits<tA, typename std::enable_if<is_col_vector<tA>::value>::type>
{
  enum {
    size = traits<tA>::rows,
    max_size = traits<tA>::max_rows
  };
  typedef typename traits<tA>::elem elem;
};

template <class tA, class tB, typename tT = void>
struct are_vector_traits_equal : public std::false_type { };

template <class tA, class tB>
struct are_vector_traits_equal<tA, tB,
    typename std::enable_if<is_vector<tA>::value && is_vector<tB>::value>::type>
: public std::integral_constant<bool, (
    (vector_traits<tA>::size == vector_traits<tB>::size) &&
    (vector_traits<tA>::max_size == vector_traits<tB>::max_size) &&
    are_elem_equal<tA, tB>::value
  )> { };

}  // namespace internal
}  // namespace lin

#endif
