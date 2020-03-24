// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../tensor.hpp"

namespace lin
{
namespace internal
{

template <class tD>
constexpr typename Tensor<tD>::Traits::elem &Tensor<tD>::operator()(size_t i, size_t j)
{
  assert(i < rows() /* Invalid row index in Tensor<...>::operator() */);
  assert(j < cols() /* Invalid col index in Tensor<...>::operator() */);
  return elements[i * cols() + j];
}

template <class tD>
constexpr typename Tensor<tD>::Traits::elem &Tensor<tD>::operator()(size_t i)
{
  assert(i < size() /* Invalid size index in Tensor<...>::operator() */);
  return elements[i];
}

template <class tD>
constexpr typename Tensor<tD>::Traits::elem const *Tensor<tD>::data() const
{
  return elements;
}

template <class tD>
constexpr typename Tensor<tD>::Traits::elem *Tensor<tD>::data()
{
  return elements;
}

template <class tD>
constexpr Tensor<tD>::Tensor(size_t r, size_t c)
{
  resize(r, c);
}

template <class tD>
constexpr Tensor<tD>::Tensor(std::initializer_list<typename Traits::elem> const &l)
{
  operator=(l);
}

template <class tD>
constexpr Tensor<tD>::Tensor(size_t r, size_t c,
    std::initializer_list<typename Traits::elem> const &l)
{
  resize(r, c);
  operator=(l);
}

template <class tD> template <class tE>
constexpr Tensor<tD>::Tensor(Stream<tE> const &E)
{
  resize(E.rows(), E.cols());
  operator=(E);
}
}  // namespace internal
}  // namespace lin
