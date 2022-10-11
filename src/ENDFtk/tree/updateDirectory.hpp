#ifndef NJOY_ENDFTK_TREE_UPDATEDIRECTORY
#define NJOY_ENDFTK_TREE_UPDATEDIRECTORY

// system includes

// other includes
#include "ENDFtk/tree/Tape.hpp"
#include "ENDFtk/tree/Material.hpp"

namespace njoy {
namespace ENDFtk {
namespace tree {

  /**
   *  @brief Update the MF1 MT451 directory for the given material
   *
   *  An exception will be thrown if the MF1 MT451 section is not present, or if
   *  there was an issue parsing it.
   */
  inline void updateDirectory( Material& material ) {

    // verify if MF1 MT451 is present
    if ( !material.hasMF( 1 ) ) {

      Log::error( "Cannot update the directory because MF1 is absent." );
      throw std::exception();
    }
    else {

      if ( !material.file( 1 ).hasMT( 451 ) ) {

        Log::error( "Cannot update the directory because MF1 MT451 is absent." );
        throw std::exception();
      }
    }

    // create the new index
    std::vector< DirectoryRecord > index;
    for ( const auto& file : material.files() ) {

      for ( const auto& section : file.sections() ) {

        index.emplace_back( section.MF(), section.MT(), section.NC(), 0 );
      }
    }

    // pop the front entry for MF1 MT451 - we will replace it
    index.erase( index.begin() );

    // parse MF1 MT451 and add the index entry for it
    auto old = material.file( 1 ).section( 451 ).parse< 1, 451 >();
    index.insert( index.begin(),
                  DirectoryRecord( 1, 451, 4 + old.NWD() + 1 + index.size(), 0 ) );

    // create a new MF1 MT451 section using the new index
    section::Type< 1, 451 > updated(
          old.ZA(), old.AWR(), old.LRP(), old.LFI(), old.NLIB(), old.NMOD(),
          old.ELIS(), old.STA(), old.LIS(), old.LISO(), old.NFOR(),
          old.AWI(), old.EMAX(), old.LREL(), old.NSUB(), old.NVER(),
          old.TEMP(), old.LDRV(),
          ranges::to< std::string >( old.description() ),
          std::move( index ), old.RTOL() );

    // replace the section in the material
    material.insertOrReplace( updated );
  }

  /**
   *  @brief Update the MF1 MT451 directory for all materials in the tape
   *
   *  An exception will be thrown if a material in the tape has no MF1 MT451
   *  section is not present, or if there was an issue parsing it.
   */
  inline void updateDirectory( Tape& tape ) {

    for ( auto& material : tape.materials() ) {

      updateDirectory( material );
    }
  }

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
