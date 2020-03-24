// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_TENSOR_STREAM_HPP_
#define LIN_INCLUDE_CORE_TENSOR_STREAM_HPP_

#include "traits.hpp"

#include <cassert>

#ifdef LIN_DESKTOP
#include <iostream>
#endif

namespace lin
{
namespace internal
{

template <class tD>
class Stream
{
  static_assert(is_traits_valid<tD>::value, "Invalid stream traits detected");

 public:
  typedef traits<tD> Traits;
  constexpr size_t rows() const;
  constexpr size_t cols() const;
  constexpr size_t size() const;
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;
  constexpr typename Traits::eval eval() const;

 protected:
  constexpr Stream() = default;
  constexpr tD const &derived() const;
  constexpr tD &derived();
};

#ifdef LIN_DESKTOP
template <class tA>
inline std::ostream &operator<<(std::ostream &os, Stream<tA> const &A);
#endif

}  // namespace internal
}  // namespace lin

#include "inl/stream.inl"

#endif
