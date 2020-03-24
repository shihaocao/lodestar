// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_TENSOR_TENSOR_HPP_
#define LIN_INCLUDE_CORE_TENSOR_TENSOR_HPP_

#include "base.hpp"
#include "generators.hpp"
#include "traits.hpp"

#include <cassert>
#include <initializer_list>

#if defined(LIN_DESKTOP) && !defined(LIN_RANDOM_SEED)
#include <ctime>
#endif

namespace lin
{
namespace internal
{

template <class tD>
class Tensor : public Base<tD>, public Dimensions<tD>
{
 public:
  typedef traits<tD> Traits;
  using Dimensions<tD>::rows;
  using Dimensions<tD>::cols;
  using Dimensions<tD>::resize;
  using Base<tD>::size;
  using Base<tD>::operator=;
  using Base<tD>::operator();
  constexpr typename Traits::elem &operator()(size_t i, size_t j);
  constexpr typename Traits::elem &operator()(size_t i);
  constexpr typename Traits::elem const *data() const;
  constexpr typename Traits::elem *data();

 protected:
  using Base<tD>::derived;
  constexpr Tensor() = default;
  constexpr Tensor(size_t r, size_t c);
  constexpr Tensor(std::initializer_list<typename Traits::elem> const &l);
  constexpr Tensor(size_t r, size_t c, std::initializer_list<typename Traits::elem> const &l);
  template <class tE>
  constexpr Tensor(Stream<tE> const &E);

 private:
  typename Traits::elem elements[Traits::max_size] = { static_cast<typename Traits::elem>(0) };
};
}  // namespace internal
}  // namespace lin

#include "inl/tensor.inl"

#endif
