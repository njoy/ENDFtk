#ifndef NJOY_ENDFTK_FILE_8
#define NJOY_ENDFTK_FILE_8

// system includes

// other includes
#include "ENDFtk/section/8.hpp"
#include "ENDFtk/file/Base.hpp"
#include "ENDFtk/file/Type.hpp"

namespace njoy {
namespace ENDFtk {
namespace file {

  template<>
  class Type< 8 > : public Base< Type< 8 > > {

    friend Base< Type >;
    using Parent = Base< Type >;

    using Text = record::Base< record::Character< 66 > >;
    using Tail = record::Tail;

    // MF8 has enumerated sectons and normal sections
    // no sections are required
    static constexpr auto requiredSections()
      RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple() )

    // MT454, MT457 and MT459 are optional
    static constexpr auto optionalSections()
      RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple( 454_c, 457_c, 459_c ) )

    // the following sections are currently unimplemented
    static constexpr auto unimplementedSections()
      RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple() )

    using Map =
    typename decltype( details::deduceMapType(
                           8_c,
                           requiredSections(),
                           optionalSections() ) )::type;

    /* fields */
    Map sectionMap;

  public:

    #include "ENDFtk/file/8/src/ctor.hpp"

    bool
    hasSection( int sectionNo ) const {

      switch ( sectionNo ) {

        case 454 : return bool( this->sectionMap[ 454_c ] );
        case 457 : return bool( this->sectionMap[ 457_c ] );
        case 459 : return bool( this->sectionMap[ 459_c ] );
        default: return false;
      }
    }

    static constexpr auto fileNumber() { return 8; }

    #include "ENDFtk/file/8/src/print.hpp"
  };

} // file namespace
} // ENDFtk namespace
} // njoy namespace

#endif
