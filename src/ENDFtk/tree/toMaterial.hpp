#ifndef NJOY_ENDFTK_TREE_TOMATERIAL
#define NJOY_ENDFTK_TREE_TOMATERIAL

// system includes

// other includes
#include "ENDFtk/Material.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace ENDFtk {
namespace tree {

  /**
   *  @brief Factory function to make a tree file from a parsed file
   *
   *  @param[in] file   the parsed file
   *  @param[in] mat    the mat number
   */
  inline Material toMaterial( const njoy::ENDFtk::Material& material ) {

    std::string buffer;
    auto output = std::back_inserter( buffer );
    material.print( output );

    auto position = buffer.begin();
    auto start = buffer.begin();
    auto end = buffer.end();
    long lineNumber = 0;

    HeadRecord head( position, end, lineNumber );

    return Material( head, start, position, end, lineNumber );
  }

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
