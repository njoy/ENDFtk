#ifndef NJOY_ENDFTK_FILE_1
#define NJOY_ENDFTK_FILE_1

// system includes

// other includes
#include "ENDFtk/section/1.hpp"
#include "ENDFtk/file/Base.hpp"
#include "ENDFtk/file/Type.hpp"

namespace njoy {
namespace ENDFtk {
namespace file {

  template<>
  class Type< 1 > : public Base< Type< 1 > > {

    friend Base< Type >;
    using Parent = Base< Type >;

    // MF1 only has enumerated sections
    // MT451 is required
    static constexpr auto requiredSections()
      RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple( 451_c ) )

    // all other sections are optional
    static constexpr auto optionalSections()
      RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple() )

    // the following sections are currently unimplemented
    static constexpr auto unimplementedSections()
      RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple( 452_c, 455_c, 456_c,
                                                     458_c, 460_c ) )

    using Map =
    typename decltype( details::deduceMapType(
                           1_c,
                           requiredSections(),
                           hana::concat( optionalSections(),
                                         unimplementedSections() ) ) )::type;

    /* fields */
    Map sectionMap;

  public :

    #include "ENDFtk/file/1/src/ctor.hpp"

    bool
    hasSection( int sectionNo ) const {

      switch( sectionNo ) {

        case 451 : return true;
        case 452 : return bool( this->sectionMap[ 452_c ] );
        case 455 : return bool( this->sectionMap[ 455_c ] );
        case 456 : return bool( this->sectionMap[ 456_c ] );
        case 458 : return bool( this->sectionMap[ 458_c ] );
        case 460 : return bool( this->sectionMap[ 460_c ] );
        default : return false;
      }
    }

    static constexpr int fileNumber() { return 1; }

    #include "ENDFtk/file/1/src/print.hpp"
  };

} // file namespace
} // ENDFtk namespace
} // njoy namespace

#endif
