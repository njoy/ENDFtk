#ifndef NJOY_ENDFTK_TREE_TOFILE
#define NJOY_ENDFTK_TREE_TOFILE

// system includes

// other includes
#include "ENDFtk/file/Type.hpp"
#include "ENDFtk/tree/File.hpp"
#include "ENDFtk/tree/toSection.hpp"

namespace njoy {
namespace ENDFtk {
namespace tree {

  /**
   *  @brief Factory function to make a tree file from a parsed file
   *
   *  @param[in] file   the parsed file
   *  @param[in] mat    the mat number
   */
  template< int MF >
  File toFile( const file::Type< MF  >& file, int mat ) {

    File tree( mat, MF );
    for ( const auto& section : file.sections() ) {

      tree.insert( toSection( section, mat ) );
    }

    return tree;
  }

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
