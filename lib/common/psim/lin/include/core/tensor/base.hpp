// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_TENSOR_BASE_HPP_
#define LIN_INCLUDE_CORE_TENSOR_BASE_HPP_

#include "stream.hpp"
#include "traits.hpp"

#include <initializer_list>
#include <type_traits>

namespace lin
{
namespace internal
{

template <class tA, class tB>
struct can_assign : public are_traits_equal<tA, tB> { };

template <class tD>
class Base : public Stream<tD>
{
 public:
  typedef traits<tD> Traits;
  using Stream<tD>::rows;
  using Stream<tD>::cols;
  using Stream<tD>::size;
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;
  constexpr typename Traits::elem &operator()(size_t i, size_t j);
  constexpr typename Traits::elem &operator()(size_t i);
  constexpr tD &operator=(std::initializer_list<typename Traits::elem> const &l);
  template <class tE, typename std::enable_if<can_assign<tD, tE>::value, size_t>::type = 0>
  constexpr tD &operator=(Stream<tE> const &E);

 protected:
  using Stream<tD>::derived;
  constexpr Base() = default;
};
}  // namespace internal
}  // namespace lin

#include "inl/base.inl"

#endif
