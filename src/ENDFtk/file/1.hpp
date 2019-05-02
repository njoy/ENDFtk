template<>
class Type< 1 > : public Base< Type< 1 > > {

  friend Base< Type >;
  using Parent = Base< Type >;

  // MF1 only has enumerated secton
  // MT451 is required
  static constexpr auto requiredSections()
    RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple( 451_c ) )

  // all other sections are optional
  static constexpr auto optionalSections()
    // hana::make_tuple( 452_c, 455_c, 456_c, 458_c, 460_c );
    RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple() )

  using Map = typename decltype( deduceMapType( 1_c,
                                                requiredSections(),
                                                optionalSections() ) )::type;

  /* fields */
  Map sectionMap;

public :

  #include "ENDFtk/file/1/src/ctor.hpp"

  bool
  hasSection( int sectionNo ) const {

    switch( sectionNo ) {

      case 451 : return true;
      /*
      case 452 : return this->sectionMap[ 452_c ];
      case 455 : return this->sectionMap[ 455_c ];
      case 456 : return this->sectionMap[ 456_c ];
      case 458 : return this->sectionMap[ 458_c ];
      case 460 : return this->sectionMap[ 460_c ];
      */
      default : return false;
    }
  }

  static constexpr int fileNumber() { return 1; }

  #include "ENDFtk/file/1/src/print.hpp"
};
