#ifndef NJOY_ENDFTK_TYPES
#define NJOY_ENDFTK_TYPES

// system includes

// other includes
#include "range/v3/view/all.hpp"
#include "range/v3/view/chunk.hpp"
#include "range/v3/view/drop_exactly.hpp"
#include "range/v3/view/take_exactly.hpp"
#include "range/v3/view/stride.hpp"

namespace njoy {
namespace ENDFtk {

  /* derived types using ranges */
  template < typename Type > using AllRange =
  decltype( ranges::cpp20::views::all( std::declval< const std::vector< Type >& >() ) );
  template < typename Range > using DropRange =
  decltype( ranges::views::drop_exactly( std::declval< Range >(), std::declval< int >() ) );
  template < typename Range > using TakeRange =
  decltype( ranges::views::take_exactly( std::declval< Range >(), std::declval< int >() ) );
  template < typename Range > using StrideRange =
  decltype( ranges::views::stride( std::declval< Range >(), std::declval< int >() ) );
  template < typename Range > using ChunkRange =
  decltype( ranges::views::chunk( std::declval< Range >(), std::declval< int >() ) );
  template < typename Range > using Chunk =
  decltype( ranges::views::chunk( std::declval< Range >(), std::declval< int >() )[ std::declval< int >() ] );

} // ENDFtk namespace
} // njoy namespace

#endif
