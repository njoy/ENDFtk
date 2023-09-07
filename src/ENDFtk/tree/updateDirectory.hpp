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
   *
   *  @param[in,out] material   the ENDF material to update
   *  @param[in]     copyMod    copy the modification number if available
   */
  inline void updateDirectory( Material& material, bool copyMod = false ) {

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

    // parse MF1 MT451 and retrieve the old index
    auto old = material.file( 1 ).section( 451 ).parse< 1, 451 >();
    decltype(auto) oldindex = old.index();

    // create the new index
    std::vector< DirectoryRecord > index;
    for ( const auto& file : material.files() ) {

      auto begin = oldindex.begin();
      for ( const auto& section : file.sections() ) {

        // get the MF and MT number for the current section
        long mf = section.MF();
        long mt = section.MT();

        // set the MOD number (if copyMod is true, retrieve the original MOD)
        // for efficiency, we assume the index to be ordered
        long mod = 0;
        if ( copyMod ) {

          auto iter = std::find_if( begin, oldindex.end(),
                                    [=] ( const auto& entry )
                                        { return ( entry.MF() == mf ) &&
                                                 ( entry.MT() == mt ); } );
          if ( iter != oldindex.end() ) {

            mod = iter->MOD();
            begin = iter;
          }
        }

        // create the new index
        index.emplace_back( mf, mt, section.NC(), mod );
      }
    }

    // replace the index for MF1 MT451
    index[0] = DirectoryRecord( 1, 451, 4 + old.NWD() + index.size(), index[0].MOD() );

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
   *
   *  @param[in,out] tape       the ENDF tape to update
   *  @param[in]     copyMod    copy the modification number if available
   */
  inline void updateDirectory( Tape& tape, bool copyMod = false ) {

    for ( auto& material : tape.materials() ) {

      updateDirectory( material, copyMod );
    }
  }

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
