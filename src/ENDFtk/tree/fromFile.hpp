#ifndef NJOY_ENDFTK_TREE_FROMFILE
#define NJOY_ENDFTK_TREE_FROMFILE

// system includes
#include <string>
#include <fstream>

// other includes
#include "Log.hpp"
#include "ENDFtk/tree/Tape.hpp"

namespace njoy {
namespace ENDFtk {
namespace tree {

  /**
   *  @brief Factory function to make a tape from a file
   *
   *  @param[in] filename   the file name
   *  @param[in] clean      option to perform basic cleanup of the ENDF tape
   */
  inline auto fromFile( const std::string& filename, bool clean = false ) {

    std::string content;
    std::ifstream in( filename,
                      std::ios::in | std::ios::binary | std::ios::ate );
    if ( not in ) {

      Log::error( "Could not open file \'{}\'", filename );
      throw std::exception();
    }

    const auto file_size = in.tellg();
    in.seekg( 0, std::ios::beg );
    content.resize( file_size / sizeof( char ) );
    in.read( &( content[ 0 ] ), file_size );

    njoy::ENDFtk::tree::Tape tape( content );
    if ( clean ) {

      tape.clean();
    }

    return tape;
  }

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
