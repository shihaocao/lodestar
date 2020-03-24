// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../stream.hpp"

namespace lin
{
namespace internal
{

template <class tD>
constexpr size_t Stream<tD>::rows() const
{
  return derived().rows();
}

template <class tD>
constexpr size_t Stream<tD>::cols() const
{
  return derived().cols();
}

template <class tD>
constexpr size_t Stream<tD>::size() const
{
  return rows() * cols();
}

template <class tD>
constexpr typename Stream<tD>::Traits::elem Stream<tD>::operator()(size_t i, size_t j) const
{
  return derived()(i, j);
}

template <class tD>
constexpr typename Stream<tD>::Traits::elem Stream<tD>::operator()(size_t i) const
{
  return derived()(i);
}

template <class tD>
constexpr typename Stream<tD>::Traits::eval Stream<tD>::eval() const
{
  return typename Traits::eval(*this);
}

template <class tD>
constexpr tD const &Stream<tD>::derived() const
{
  return static_cast<tD const &>(*this);
}

template <class tD>
constexpr tD &Stream<tD>::derived()
{
  return static_cast<tD &>(*this);
}

#ifdef LIN_DESKTOP
template <class tA>
inline std::ostream &operator<<(std::ostream &os, Stream<tA> const &A)
{
  for (size_t i = 0; i < A.rows() - 1; i++) {
    for (size_t j = 0; j < A.cols() - 1; j++)
      os << A(i, j) << " ";
    os << A(i, A.cols() - 1) << "\n";
  }
  for (size_t j = 0; j < A.cols() - 1; j++)
    os << A(A.rows() - 1, j) << " ";
  os << A(A.rows() - 1, A.cols() - 1) << "\n";
  return os;
}
#endif

}  // namespace internal
}  // namespace  lin
