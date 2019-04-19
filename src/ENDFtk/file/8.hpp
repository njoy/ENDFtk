template<>
class Type< 8 > : public Base< Type< 8 > >,
                  public SpecialBase< Type< 8 > > {

  friend SpecialBase< Type< 8 > >;

  /* MF8 has enumerated sections */
  static constexpr auto optionalSections() { return hana::make_tuple( /*454_c,*/ 457_c/*, 457_c*/ ); }
  static constexpr auto sections() { return optionalSections(); }

  /* convenience typedefs */
  using Map =
    decltype
    ( hana::make_map
      ( /* hana::make_pair
        ( 454_c, std::declval< std::optional< section::Type< 8, 454 > > >() ), */
        hana::make_pair
        ( 457_c, std::declval< std::optional< section::Type< 8, 457 > > >() ) /*,
        hana::make_pair
        ( 459_c, std::declval< std::optional< section::Type< 8, 457 > > >() )
        */
        ) );

  /* fields */
  Map sectionMap;

  /* auxiliary functions */
  #include "ENDFtk/file/8/src/read.hpp"
  #include "ENDFtk/file/8/src/fill.hpp"

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
