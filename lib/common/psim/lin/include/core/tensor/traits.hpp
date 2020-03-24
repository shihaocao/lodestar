// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_TENSOR_TRAITS_HPP_
#define LIN_INCLUDE_CORE_TENSOR_TRAITS_HPP_

#include <type_traits>

#if defined(_WIN32) || defined(__APPLE__) || defined(__linux__) || \
    defined(__unix__) || defined(_POSIX_VERION)
#define LIN_DESKTOP
#endif

namespace lin
{

typedef unsigned int size_t;

namespace internal
{

template <class tA, typename tT = void>
struct elem;

template <class tA>
struct is_elem_valid : public std::integral_constant<bool, (
    std::is_same<typename elem<tA>::type, float>::value ||
    std::is_same<typename elem<tA>::type, double>::value
  )> { };

template <class tA, class tB>
struct are_elem_equal : public std::is_same<typename elem<tA>::type, typename elem<tB>::type> { };

template <class tA, typename tT = void>
struct eval;

template <class tA>
struct is_eval_valid : public std::true_type { };

template <class tA, class tB>
struct are_eval_equal : public std::is_same<typename eval<tA>::type, typename eval<tB>::type> { };

template <class tA, typename tT = void>
struct dims;

template <class tA>
struct has_fixed_rows : public std::integral_constant<bool, (
    (dims<tA>::rows == dims<tA>::max_rows) && (dims<tA>::rows > 0)
  )> { };

template <class tA>
struct has_fixed_cols : public std::integral_constant<bool, (
    (dims<tA>::cols == dims<tA>::max_cols) && (dims<tA>::cols > 0)
  )> { };

template <class tA>
struct has_fixed_size : public std::integral_constant<bool,
    (has_fixed_rows<tA>::value && has_fixed_cols<tA>::value
  )> { };

template <class tA>
struct has_static_rows : public std::integral_constant<bool, (
    (dims<tA>::rows == 0) && (dims<tA>::max_rows > 0)
  )> { };

template <class tA>
struct has_static_cols : public std::integral_constant<bool, (
    (dims<tA>::cols == 0) && (dims<tA>::max_cols > 0)
  )> { };

template <class tA>
struct has_static_size : public std::integral_constant<bool, (
    (has_static_rows<tA>::value && has_static_cols<tA>::value) ||
    (has_static_rows<tA>::value && has_fixed_cols<tA>::value) ||
    (has_fixed_rows<tA>::value && has_static_cols<tA>::value)
  )> { };

template <class tA>
struct is_dims_valid : public std::integral_constant<bool, (
    has_fixed_size<tA>::value || has_static_size<tA>::value
  )> { };

template <class tA, class tB>
struct are_dims_equal : public std::integral_constant<bool, (
    (dims<tA>::rows == dims<tB>::rows) && (dims<tA>::cols == dims<tB>::cols) &&
    (dims<tA>::max_rows == dims<tB>::max_rows) && (dims<tA>::max_cols == dims<tB>::max_cols)
  )> { };

template <class tA>
struct traits
{
  enum {
    rows = dims<tA>::rows,
    cols = dims<tA>::cols,
    max_rows = dims<tA>::max_rows,
    max_cols = dims<tA>::max_cols,
    max_size = max_rows * max_cols
  };
  typedef typename elem<tA>::type elem;
  typedef typename eval<tA>::type eval;
};

template <class tA>
struct is_traits_valid : public std::integral_constant<bool, (
    is_elem_valid<tA>::value && is_eval_valid<tA>::value && is_dims_valid<tA>::value
  )> { };

template <class tA, class tB>
struct are_traits_equal : public std::integral_constant<bool, (
    are_elem_equal<tA, tB>::value && are_eval_equal<tA, tB>::value && are_dims_equal<tA, tB>::value
  )> { };

}  // namespace internal
}  // namespace lin

#endif
