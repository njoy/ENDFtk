template<>
class Type< 8 > : public Base< Type< 8 > > {

  friend Base< Type >;
  using Parent = Base< Type >;

  // MF8 has enumerated sectons and normal sections
  // no sections are required
  static constexpr auto requiredSections()
    RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple() )

  // MT2 and MT4 are optional
  static constexpr auto optionalSections()
    // hana::make_tuple( 454_c, 457_c, 459_c );
    RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple( 457_c ) )

  using Map = typename decltype( deduceMapType( 8_c,
                                                requiredSections(),
                                                optionalSections() ) )::type;

  /* fields */
  Map sectionMap;

public:

  #include "ENDFtk/file/8/src/ctor.hpp"

  bool
  hasSection( int sectionNo ) const {

    switch ( sectionNo ) {

      /* case 454 : return bool( this->sectionMap[ 454_c ] ); */
      case 457 : return bool( this->sectionMap[ 457_c ] );
      /* case 459 : return bool( this->sectionMap[ 459_c ] ); */
      default: return false;
    }
  }

  static constexpr auto fileNumber() { return 8; }

  #include "ENDFtk/file/8/src/print.hpp"
};
