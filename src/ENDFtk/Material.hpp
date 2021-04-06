#ifndef NJOY_ENDFTK_MATERIAL
#define NJOY_ENDFTK_MATERIAL

// system includes

// other includes
#include "ENDFtk/file/1.hpp"
#include "ENDFtk/file/2.hpp"
#include "ENDFtk/file/3.hpp"
#include "ENDFtk/file/4.hpp"
#include "ENDFtk/file/5.hpp"
#include "ENDFtk/file/6.hpp"
#include "ENDFtk/file/7.hpp"
#include "ENDFtk/file/8.hpp"
#include "ENDFtk/file/9.hpp"
#include "ENDFtk/file/10.hpp"
#include "ENDFtk/file/12.hpp"
#include "ENDFtk/file/13.hpp"
#include "ENDFtk/file/14.hpp"
#include "ENDFtk/file/15.hpp"
#include "ENDFtk/file/23.hpp"
#include "ENDFtk/file/26.hpp"
#include "ENDFtk/file/27.hpp"
#include "ENDFtk/file/28.hpp"
#include "ENDFtk/file/30.hpp"
#include "ENDFtk/file/31.hpp"
#include "ENDFtk/file/32.hpp"
#include "ENDFtk/file/33.hpp"
#include "ENDFtk/file/34.hpp"
#include "ENDFtk/file/35.hpp"
#include "ENDFtk/file/40.hpp"
#include "boost/hana.hpp"

namespace njoy {
namespace ENDFtk {

  class Material {

    // MF1 is required
    static constexpr auto requiredFiles()
      RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple( 1_c ) )

    // all other files are optional
    static constexpr auto optionalFiles()
      RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple( 2_c, 3_c, 4_c, 5_c, 6_c,
                                                     7_c, 8_c, 9_c, 10_c,
                                                     12_c, 13_c, 14_c ) )

    // the following files are currently unimplemented
    static constexpr auto unimplementedFiles()
      RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple( 15_c,
                                                     23_c, 26_c, 27_c, 28_c,
                                                     30_c, 31_c, 32_c, 33_c,
                                                     34_c, 35_c, 40_c ) )

    // convenience function to retrieve all file numbers that can be parsed
    static constexpr auto files() {

      return hana::sort( hana::concat( requiredFiles(),
                                       hana::concat(
                                         optionalFiles(),
                                         unimplementedFiles() ) ) );
    }

    /* auxiliary functions */
    #include "ENDFtk/Material/src/fill.hpp"
    #include "ENDFtk/Material/src/read.hpp"
    #include "ENDFtk/Material/src/verifyEND.hpp"

    using Map =
    typename decltype( details::deduceMapType(
                           requiredFiles(),
                           hana::concat( optionalFiles(),
                                         unimplementedFiles() ) ) )::type;

    /* fields */
    int mat_;
    Map fileMap;

  public:

    /* constructors */
    #include "ENDFtk/Material/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the material number
     */
    int MAT() const { return this->mat_; }

    /**
     *  @brief Return the material number
     */
    int materialNumber() const { return this->MAT(); }

    #include "ENDFtk/Material/src/file.hpp"

    /**
     *  @brief Retrieve a specific file
     *
     *  @param mf   the MF number of the file to be retrieved
     */
    template< typename Index >
    constexpr decltype( auto ) MF( Index mf ) const { return this->file( mf ); }

    /**
     *  @brief Retrieve a specific file
     *
     *  @param mf   the MF number of the file to be retrieved
     */
    template< typename Index > constexpr decltype( auto ) MF( Index mf ) {

      return this->file( mf );
    }

    /**
     *  @brief Verify if a given file (defined by the MF number) is defined
     *
     *  @param mf   the MF number of the file to be verified
     */
    bool hasFile( int mf ) const {

      switch( mf ) {

        case 1: return true;
        case 2: return bool( this->fileMap[ 2_c ] );
        case 3: return bool( this->fileMap[ 3_c ] );
        case 4: return bool( this->fileMap[ 4_c ] );
        case 5: return bool( this->fileMap[ 5_c ] );
        case 6: return bool( this->fileMap[ 6_c ] );
        case 7: return bool( this->fileMap[ 7_c ] );
        case 8: return bool( this->fileMap[ 8_c ] );
        case 9: return bool( this->fileMap[ 9_c ] );
        case 10: return bool( this->fileMap[ 10_c ] );
        case 12: return bool( this->fileMap[ 12_c ] );
        case 13: return bool( this->fileMap[ 13_c ] );
        case 14: return bool( this->fileMap[ 14_c ] );
        case 15: return bool( this->fileMap[ 15_c ] );
        case 23: return bool( this->fileMap[ 23_c ] );
        case 26: return bool( this->fileMap[ 26_c ] );
        case 27: return bool( this->fileMap[ 27_c ] );
        case 28: return bool( this->fileMap[ 28_c ] );
        case 30: return bool( this->fileMap[ 30_c ] );
        case 31: return bool( this->fileMap[ 31_c ] );
        case 32: return bool( this->fileMap[ 32_c ] );
        case 33: return bool( this->fileMap[ 33_c ] );
        case 34: return bool( this->fileMap[ 34_c ] );
        case 35: return bool( this->fileMap[ 35_c ] );
        case 40: return bool( this->fileMap[ 40_c ] );
        default: return false;
      }
    }

    /**
     *  @brief Verify if a given file (defined by the MF number) is defined
     *
     *  @param mf   the MF number of the file to be verified
     */
    bool hasMF( int mf ) const {

      return this->hasFile( mf );
    }

    #include "ENDFtk/Material/src/print.hpp"
  };

} // ENDFtk namespace
} // njoy namespace

#endif
