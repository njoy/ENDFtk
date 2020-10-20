#ifndef NJOY_ENDFTK_FILE_TYPE
#define NJOY_ENDFTK_FILE_TYPE

// system includes

// other includes
#include "range/v3/front.hpp"
#include "range/v3/view/map.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/file/Base.hpp"

namespace njoy {
namespace ENDFtk {
namespace file {

  template< int FileNumber >
  class Type : public Base< Type< FileNumber > > {

  public :

    /* convenience typedefs */
    using Section = section::Type< FileNumber >;

  protected :

    /* fields */
    std::map< int, Section > sectionMap;

    /* methods */
    #include "ENDFtk/file/Type/src/insert.hpp"
    #include "ENDFtk/file/Type/src/fill.hpp"
    #include "ENDFtk/file/Type/src/read.hpp"

  public :

    #include "ENDFtk/file/Type/src/ctor.hpp"
    #include "ENDFtk/file/Type/src/section.hpp"

    auto sections() { return this->sectionMap | ranges::view::values; }
    auto sections() const { return this->sectionMap | ranges::view::values; }

    auto begin() { return this->sections().begin(); }
    auto end() { return this->sections().end(); }

    auto begin() const { return this->sections().begin(); }
    auto end() const { return this->sections().end(); }

    bool hasSection( int sectionNo ) const {

      return this->sectionMap.count( sectionNo );
    }

    static int fileNumber() { return FileNumber; }

    #include "ENDFtk/file/Type/src/print.hpp"
  };

} // file namespace
} // ENDFtk namespace
} // njoy namespace

#endif
