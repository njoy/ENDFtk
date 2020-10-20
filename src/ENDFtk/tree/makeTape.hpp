#ifndef NJOY_ENDFTK_TREE_MAKETAPE
#define NJOY_ENDFTK_TREE_MAKETAPE

// system includes

// other includes
#include "ENDFtk/tree/Tape.hpp"

namespace njoy {
namespace ENDFtk {
namespace tree {

  template< typename Range >
  auto makeTape( Range&& range ) {

    return Tape< Range >{ std::forward< Range >( range ) };
  }

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
