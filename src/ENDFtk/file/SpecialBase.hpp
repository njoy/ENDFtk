template < typename Derived >
class SpecialBase {

  /* auxiliary functions */
  #include "ENDFtk/file/SpecialBase/src/get.hpp"

public:

  /* get methods */
  #include "ENDFtk/file/SpecialBase/src/section.hpp"

  template< typename Index > decltype( auto ) MT( Index sectionNo ) const {

    return this->section( sectionNo );
  }

  template< typename Index > decltype( auto ) MT( Index sectionNo ) {

    return this->section( sectionNo );
  }
};
