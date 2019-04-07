template<>
class Type< 7 > {

  /* MF7 has a limited number of possible sections (all optional) */
  static constexpr auto optionalSections = hana::make_tuple( 2_c, 4_c );
//  static constexpr auto sections = optionalSections;
  static constexpr auto getSections() { return optionalSections; }

  /* convenience typedefs */
  using Map =
    decltype
    ( hana::make_map
      ( hana::make_pair
        ( 2_c, std::declval< std::optional< section::Type< 7, 2 > > >() ),
        hana::make_pair
        ( 4_c, std::declval< std::optional< section::Type< 7, 4 > > >() ) ) );

  /* fields */
  Map sectionMap;

  /* auxiliary functions */
  #include "ENDFtk/file/7/src/get.hpp"
  #include "ENDFtk/file/7/src/read.hpp"
  #include "ENDFtk/file/7/src/fill.hpp"

public:

  #include "ENDFtk/file/7/src/ctor.hpp"

  #include "ENDFtk/file/7/src/sectionNumber.hpp"

  template< typename Index >
  decltype(auto) MT( Index sectionNo ) const {
    return this->sectionNumber( sectionNo );
  }

  template< typename Index >
  decltype(auto) MT( Index sectionNo ) {
    return this->sectionNumber( sectionNo );
  }

  bool
  hasMT( int sectionNo ) const {
    switch( sectionNo ){
    case 2: return bool( this->sectionMap[ 2_c ] );
    case 4: return bool( this->sectionMap[ 4_c ] );
    default: return false;
    }
  }

  bool
  hasSectionNumber( int sectionNo ) const { return this->hasMT( sectionNo ); }

  static constexpr auto MF(){ return 7; }
  static constexpr auto fileNumber(){ return MF(); }

  #include "ENDFtk/file/7/src/print.hpp"
};
