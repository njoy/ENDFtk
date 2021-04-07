#ifndef NJOY_ENDFTK_TYPES
#define NJOY_ENDFTK_TYPES

// system includes

// other includes
#include "range/v3/view/all.hpp"

namespace njoy {
namespace ENDFtk {

  /* derived types using ranges */
  template < typename Type > using AllRange =
  decltype( ranges::cpp20::views::all( std::declval< const std::vector< Type >& >() ) );

  /* type aliases */
  using DoubleRange = AllRange< double >;
  using LongRange = AllRange< long >;

} // ENDFtk namespace
} // njoy namespace

#endif
