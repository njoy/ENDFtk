template<>
class Type< 2 > : public Base< Type< 2 > > {

  friend Base< Type >;
  using Parent = Base< Type >;

  // MF2 only has enumerated sections
  // MT151 is required
  static constexpr auto requiredSections()
    RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple( 151_c ) )

  // all other sections are optional
  static constexpr auto optionalSections()
    RANGES_DECLTYPE_AUTO_RETURN( hana::make_tuple( 152_c ) )

  using Map = typename decltype( deduceMapType( 2_c,
                                                requiredSections(),
                                                optionalSections() ) )::type;

  /* fields */
  Map sectionMap;

public :

  #include "ENDFtk/file/2/src/ctor.hpp"

  bool
  hasSection( int sectionNo ) const {

    switch( sectionNo ) {

      case 151 : return true;
      case 152 : return this->sectionMap[ 152_c ];
      // case 153 : return this->sectionMap[ 153_c ];
      default : return false;
    }
  }

  static constexpr int fileNumber() { return 2; }

  #include "ENDFtk/file/2/src/print.hpp"
};
