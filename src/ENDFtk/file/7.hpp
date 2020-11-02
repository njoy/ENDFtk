#ifndef NJOY_ENDFTK_FILE_7
#define NJOY_ENDFTK_FILE_7

// system includes

// other includes
#include "ENDFtk/section/7.hpp"
#include "ENDFtk/file/Base.hpp"
#include "ENDFtk/file/Type.hpp"

namespace njoy {
namespace ENDFtk {
namespace file {

  template<>
  class Type< 7 > : public Base< Type< 7 > > {

    friend Base< Type >;
    using Parent = Base< Type >;

    // MF7 only has enumerated secton
    // no sections are required
    static constexpr auto requiredSections()
      RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple() )

    // MT2 and MT4 are optional
    static constexpr auto optionalSections()
      RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple( 2_c, 4_c ) )

    using Map =
    typename decltype( details::deduceMapType( 7_c,
                                               requiredSections(),
                                               optionalSections() ) )::type;

    /* fields */
    Map sectionMap;

  public:

    #include "ENDFtk/file/7/src/ctor.hpp"

    bool
    hasSection( int sectionNo ) const {

      switch ( sectionNo ) {

        case 2: return bool( this->sectionMap[ 2_c ] );
        case 4: return bool( this->sectionMap[ 4_c ] );
        default: return false;
      }
    }

    static constexpr auto fileNumber() { return 7; }

    #include "ENDFtk/file/7/src/print.hpp"
  };

} // file namespace
} // ENDFtk namespace
} // njoy namespace

#endif
