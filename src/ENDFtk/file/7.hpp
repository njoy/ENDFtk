template<>
class Type< 7 > : public Base< Type< 7 > > {

  using Parent = Base< Type >;

  /* MF7 has a limited number of possible sections (all optional) */
  static constexpr auto requiredSections() RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple() )
  static constexpr auto optionalSections() RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple( 2_c, 4_c ) )

  using Map = typename decltype( deduceMapType( 7_c,
                                                requiredSections(),
                                                optionalSections() ) )::type;

  /* fields */
  Map sectionMap;

  /* auxiliary functions */
  #include "ENDFtk/file/7/src/read.hpp"
  #include "ENDFtk/file/7/src/fill.hpp"

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
