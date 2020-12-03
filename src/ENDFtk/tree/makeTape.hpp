#ifndef NJOY_ENDFTK_TREE_MAKETAPE
#define NJOY_ENDFTK_TREE_MAKETAPE

// system includes

// other includes
#include "ENDFtk/tree/Tape.hpp"

namespace njoy {
namespace ENDFtk {
namespace tree {

  /**
   *  @brief Factory function to make a tape from a buffer
   *
   *  @param[in] buffer   the tape buffer (e.g. a string)
   */
  template< typename Buffer >
  auto makeTape( Buffer&& buffer ) {

    return Tape< Buffer >{ std::forward< Buffer >( buffer ) };
  }

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
