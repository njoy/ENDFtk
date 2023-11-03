#ifndef NJOY_ENDFTK_FILE_32
#define NJOY_ENDFTK_FILE_32

// system includes

// other includes
#include "ENDFtk/section/32.hpp"
#include "ENDFtk/file/Base.hpp"
#include "ENDFtk/file/Type.hpp"

namespace njoy {
namespace ENDFtk {
namespace file {

  template<>
  class Type< 32 > : public Base< Type< 32 > > {

    friend Base< Type >;
    using Parent = Base< Type >;

    // MF32 only has enumerated secton
    // no sections are required
    static constexpr auto requiredSections()
      RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple( 151_c ) )

    // no optional sections
    static constexpr auto optionalSections()
      RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple() )

    // no sections are currently unimplemented
    static constexpr auto unimplementedSections()
      RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple() )

    using Map =
    typename decltype( details::deduceMapType(
                           32_c,
                           requiredSections(),
                           optionalSections() ) )::type;

    /* fields */
    Map sectionMap;

  public:

    #include "ENDFtk/file/32/src/ctor.hpp"

    bool
    hasSection( int sectionNo ) const {

      switch ( sectionNo ) {

        case 151 : return true;
        default: return false;
      }
    }

    static constexpr auto fileNumber() { return 32; }

    #include "ENDFtk/file/32/src/print.hpp"
  };

} // file namespace
} // ENDFtk namespace
} // njoy namespace

#endif
