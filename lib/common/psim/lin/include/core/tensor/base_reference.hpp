// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_TENSOR_BASE_REFERENCE_HPP_
#define LIN_INCLUDE_CORE_TENSOR_BASE_REFERENCE_HPP_

#include "base.hpp"
#include "dimensions.hpp"

#include <cassert>

namespace lin
{
namespace internal
{

template <size_t tR, size_t tC, size_t tMR, size_t tMC, class tE>
class BaseReference : public Base<BaseReference<tR, tC, tMR, tMC, tE>>,
    public Dimensions<BaseReference<tR, tC, tMR, tMC, tE>>
{
 public:
  typedef traits<BaseReference<tR, tC, tMR, tMC, tE>> Traits;
  using Dimensions<BaseReference<tR, tC, tMR, tMC, tE>>::rows;
  using Dimensions<BaseReference<tR, tC, tMR, tMC, tE>>::cols;
  using Base<BaseReference<tR, tC, tMR, tMC, tE>>::size;
  using Base<BaseReference<tR, tC, tMR, tMC, tE>>::operator=;
  using Base<BaseReference<tR, tC, tMR, tMC, tE>>::operator();
  constexpr BaseReference() = delete;
  constexpr BaseReference(Base<tE> &E, size_t i, size_t j, size_t r, size_t c);
  constexpr typename Traits::elem &operator()(size_t i, size_t j);
  constexpr typename Traits::elem &operator()(size_t i);

 private:
  using Dimensions<BaseReference<tR, tC, tMR, tMC, tE>>::resize;
  using Base<BaseReference<tR, tC, tMR, tMC, tE>>::derived;
  Base<tE> &E;
  size_t const i;
  size_t const j;
};

template <size_t tR, size_t tC, size_t tMR, size_t tMC, class tE>
struct elem<BaseReference<tR, tC, tMR, tMC, tE>> : public elem<tE> { };

template <size_t tR, size_t tC, size_t tMR, size_t tMC, class tE>
struct dims<BaseReference<tR, tC, tMR, tMC, tE>>
{
  enum {
    rows = tR,
    cols = tC,
    max_rows = tMR,
    max_cols = tMC
  };
};
}  // namespace internal

/** @fn ref
 *  @param[in] E Backing stream the reference pulls data from.
 *  @param[in] i Row offset of the reference in the backing stream.
 *  @param[in] j Column offset of the reference in in the backing stream.
 *  @param[in] r Resizes the references row count.
 *  @param[in] c Resizes the references column count.
 *  
 *  Generates a statically sized, read/write reference to the provided backing
 *  stream. If you are looking to reference a full row/column of a tensor, see
 *  the row and column reference functions. */
template <size_t tR, size_t tC, size_t tMR, size_t tMC, class tE>
constexpr internal::BaseReference<tR, tC, tMR, tMC, tE>
ref(internal::Base<tE> &E, size_t i, size_t j, size_t r = tMR, size_t c = tMC);

/** @fn ref
 *  @param[in] E Backing stream the reference pulls data from.
 *  @param[in] i Row offset of the reference in the backing stream.
 *  @param[in] j Column offset of the reference in in the backing stream.
 *  
 *  Generates a fixed sized, read/write reference to the provided backing
 *  stream. If you are looking to reference a full row/column of a tensor, see
 *  the row and column reference functions. */
template <size_t tR, size_t tC, class tE>
constexpr internal::BaseReference<tR, tC, tR, tC, tE>
ref(internal::Base<tE> &E, size_t i, size_t j);

/** @fn ref_row
 *  @param[in] E Backing stream the reference pulls data from.
 *  @param[in] i Row index to be referenced.
 * 
 *  Generates a read/write reference to the i'th row of the provided stream as a
 *  row vector. This function is a small wrapper around the standard ref
 *  function using the traits of _E and E's dimensions at runtime. */
template <class tE>
constexpr auto ref_row(internal::Base<tE> &E, size_t i);

/** @fn ref_row
 *  @param[in] E Backing stream the reference pulls data from.
 *  @param[in] i Column index to be referenced.
 * 
 *  Generates a read/writee only reference to the j'th column of the provided
 *  stream as a column vector. This function is a small wrapper around the
 *  standard ref function using the traits of _E and E's dimensions at runtime.
 *  */
template <class tE>
constexpr auto ref_col(internal::Base<tE> &E, size_t j);

}  // namespace lin

#include "inl/base_reference.inl"

#endif
