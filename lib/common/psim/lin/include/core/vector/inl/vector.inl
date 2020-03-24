// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../vector.hpp"

namespace lin
{

template <typename tT, size_t tN, size_t tMN>
constexpr RowVector<tT, tN, tMN>::RowVector(size_t n)
: internal::Tensor<RowVector<tT, tN, tMN>>(1, n) { }

template <typename tT, size_t tN, size_t tMN>
constexpr RowVector<tT, tN, tMN>::RowVector(size_t r, size_t c)
: internal::Tensor<RowVector<tT, tN, tMN>>(r, c) { }

template <typename tT, size_t tN, size_t tMN>
constexpr RowVector<tT, tN, tMN>::RowVector(std::initializer_list<typename Traits::elem> const &l)
: internal::Tensor<RowVector<tT, tN, tMN>>(l) { }

template <typename tT, size_t tN, size_t tMN>
constexpr RowVector<tT, tN, tMN>::RowVector(size_t n,
    std::initializer_list<typename Traits::elem> const &l)
: internal::Tensor<RowVector<tT, tN, tMN>>(1, n, l) { }

template <typename tT, size_t tN, size_t tMN>
constexpr RowVector<tT, tN, tMN>::RowVector(size_t r, size_t c,
    std::initializer_list<typename Traits::elem> const &l)
: internal::Tensor<RowVector<tT, tN, tMN>>(r, c, l) { }

template <typename tT, size_t tN, size_t tMN> template <class tE>
constexpr RowVector<tT, tN, tMN>::RowVector(internal::Stream<tE> const &E)
: internal::Tensor<RowVector<tT, tN, tMN>>(E) { }

template <typename tT, size_t tN, size_t tMN>
constexpr void RowVector<tT, tN, tMN>::resize(size_t n)
{
  resize(1, n);
}

template <typename tT, size_t tN, size_t tMN>
constexpr Vector<tT, tN, tMN>::Vector(size_t n)
: internal::Tensor<Vector<tT, tN, tMN>>(n, 1) { }

template <typename tT, size_t tN, size_t tMN>
constexpr Vector<tT, tN, tMN>::Vector(size_t r, size_t c)
: internal::Tensor<Vector<tT, tN, tMN>>(r, c) { }

template <typename tT, size_t tN, size_t tMN>
constexpr Vector<tT, tN, tMN>::Vector(std::initializer_list<typename Traits::elem> const &l)
: internal::Tensor<Vector<tT, tN, tMN>>(l) { }

template <typename tT, size_t tN, size_t tMN>
constexpr Vector<tT, tN, tMN>::Vector(size_t n,
    std::initializer_list<typename Traits::elem> const &l)
: internal::Tensor<Vector<tT, tN, tMN>>(n, 1, l) { }

template <typename tT, size_t tN, size_t tMN>
constexpr Vector<tT, tN, tMN>::Vector(size_t r, size_t c,
    std::initializer_list<typename Traits::elem> const &l)
: internal::Tensor<Vector<tT, tN, tMN>>(r, c, l) { }

template <typename tT, size_t tN, size_t tMN> template <class tE>
constexpr Vector<tT, tN, tMN>::Vector(internal::Stream<tE> const &E)
: internal::Tensor<Vector<tT, tN, tMN>>(E) { }

template <typename tT, size_t tN, size_t tMN>
constexpr void Vector<tT, tN, tMN>::resize(size_t n)
{
  resize(n, 1);
}
}  // namespace lin
