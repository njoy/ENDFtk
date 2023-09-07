#ifndef NJOY_ENDFTK_TREE_TOSECTION
#define NJOY_ENDFTK_TREE_TOSECTION

// system includes

// other includes
#include "ENDFtk/tree/Section.hpp"

namespace njoy {
namespace ENDFtk {
namespace tree {

  /**
   *  @brief Factory function to make a tree section from a parsed section
   *
   *  @param[in] section   the parsed section
   */
  template< int MF, int... OptionalMT >
  Section toSection( const section::Type< MF, OptionalMT... >& section,
                     int mat ) {

    std::string buffer;
    auto output = std::back_inserter( buffer );
    section.print( output, mat, MF );

    return Section( mat, MF, section.MT(), std::move( buffer ) );
  }

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
