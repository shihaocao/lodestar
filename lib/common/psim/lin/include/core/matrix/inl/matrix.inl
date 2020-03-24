// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#include "../matrix.hpp"

namespace lin
{

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
constexpr Matrix<tT, tR, tC, tMR, tMC>::Matrix(size_t r, size_t c)
: internal::Tensor<Matrix<tT, tR, tC, tMR, tMC>>(r, c) { }

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
constexpr Matrix<tT, tR, tC, tMR, tMC>::Matrix(std::initializer_list<typename Traits::elem> const &l)
: internal::Tensor<Matrix<tT, tR, tC, tMR, tMC>>(l) { }

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC>
constexpr Matrix<tT, tR, tC, tMR, tMC>::Matrix(size_t r, size_t c,
    std::initializer_list<typename Traits::elem> const &l)
: internal::Tensor<Matrix<tT, tR, tC, tMR, tMC>>(r, c, l) { }

template <typename tT, size_t tR, size_t tC, size_t tMR, size_t tMC> template <class tE>
constexpr Matrix<tT, tR, tC, tMR, tMC>::Matrix(internal::Stream<tE> const &E)
: internal::Tensor<Matrix<tT, tR, tC, tMR, tMC>>(E) { }

}  // namespace lin
