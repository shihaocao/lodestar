// vim: set tabstop=2:softtabstop=2:shiftwidth=2:noexpandtab

#ifndef LIN_INCLUDE_CORE_TENSOR_STREAM_REFERENCE_HPP_
#define LIN_INCLUDE_CORE_TENSOR_STREAM_REFERENCE_HPP_

#include "dimensions.hpp"
#include "stream.hpp"
#include "traits.hpp"

#include <cassert>

namespace lin
{
namespace internal
{

template <size_t tR, size_t tC, size_t tMR, size_t tMC, class tE>
class StreamReference : public Stream<StreamReference<tR, tC, tMR, tMC, tE>>,
    public Dimensions<StreamReference<tR, tC, tMR, tMC, tE>>
{
 public:
  typedef traits<StreamReference<tR, tC, tMR, tMC, tE>> Traits;
  using Dimensions<StreamReference<tR, tC, tMR, tMC, tE>>::rows;
  using Dimensions<StreamReference<tR, tC, tMR, tMC, tE>>::cols;
  using Stream<StreamReference<tR, tC, tMR, tMC, tE>>::size;
  constexpr StreamReference() = delete;
  constexpr StreamReference(Stream<tE> const &E, size_t i, size_t j, size_t r, size_t c);
  constexpr typename Traits::elem operator()(size_t i, size_t j) const;
  constexpr typename Traits::elem operator()(size_t i) const;

 private:
  using Dimensions<StreamReference<tR, tC, tMR, tMC, tE>>::resize;
  using Stream<StreamReference<tR, tC, tMR, tMC, tE>>::derived;
  Stream<tE> const &E;
  size_t const i;
  size_t const j;
};

template <size_t tR, size_t tC, size_t tMR, size_t tMC, class tE>
struct elem<StreamReference<tR, tC, tMR, tMC, tE>> : public elem<tE> { };

template <size_t tR, size_t tC, size_t tMR, size_t tMC, class tE>
struct dims<StreamReference<tR, tC, tMR, tMC, tE>>
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
 *  Generates a statically sized, read only reference to the provided backing
 *  stream. If you are looking to reference a full row/column of a tensor, see
 *  the row and column reference functions. */
template <size_t tR, size_t tC, size_t tMR, size_t tMC, class tE>
constexpr internal::StreamReference<tR, tC, tMR, tMC, tE> const
ref(internal::Stream<tE> const &E, size_t i, size_t j, size_t r = tMR, size_t c = tMC);

/** @fn ref
 *  @param[in] E Backing stream the reference pulls data from.
 *  @param[in] i Row offset of the reference in the backing stream.
 *  @param[in] j Column offset of the reference in in the backing stream.
 *  
 *  Generates a fixed sized, read only reference to the provided backing stream.
 *  If you are looking to reference a full row/column of a tensor, see the row
 *  and column reference functions. */
template <size_t tR, size_t tC, class tE>
constexpr internal::StreamReference<tR, tC, tR, tC, tE> const
ref(internal::Stream<tE> const &E, size_t i, size_t j);

/** @fn ref_row
 *  @param[in] E Backing stream the reference pulls data from.
 *  @param[in] i Row index to be referenced.
 * 
 *  Generates a read only reference to the i'th row of the provided stream as a
 *  row vector. This function is a small wrapper around the standard ref
 *  function using the traits of _E and E's dimensions at runtime. */
template <class tE>
constexpr auto ref_row(internal::Stream<tE> const &E, size_t i);

/** @fn ref_row
 *  @param[in] E Backing stream the reference pulls data from.
 *  @param[in] i Column index to be referenced.
 * 
 *  Generates a read only reference to the j'th column of the provided stream as
 *  a column vector. This function is a small wrapper around the standard ref
 *  function using the traits of _E and E's dimensions at runtime. */
template <class tE>
constexpr auto ref_col(internal::Stream<tE> const &E, size_t j);

}  // namespace lin

#include "inl/stream_reference.inl"

#endif
