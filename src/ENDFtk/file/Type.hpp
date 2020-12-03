#ifndef NJOY_ENDFTK_FILE_TYPE
#define NJOY_ENDFTK_FILE_TYPE

// system includes
#include <map>

// other includes
#include "range/v3/front.hpp"
#include "range/v3/view/map.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/file/Base.hpp"

namespace njoy {
namespace ENDFtk {
namespace file {

  /**
   *  @class
   *  @brief Generic file class
   */
  template< int FileNumber >
  class Type : public Base< Type< FileNumber > > {

  public :

    /* type aliases */
    using Section = section::Type< FileNumber >;

  protected :

    /* fields */
    std::map< int, Section > sectionMap;

    /* auxialiary functions */
    #include "ENDFtk/file/Type/src/insert.hpp"
    #include "ENDFtk/file/Type/src/fill.hpp"
    #include "ENDFtk/file/Type/src/read.hpp"

  public :

    /* constructors */
    #include "ENDFtk/file/Type/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the sections stored in this file
     */
    auto sections() { return this->sectionMap | ranges::view::values; }

    /**
     *  @brief Return the sections stored in this file
     */
    auto sections() const { return this->sectionMap | ranges::view::values; }

    /**
     *  @brief Return an iterator to the start of the sections
     */
    auto begin() { return this->sections().begin(); }

    /**
     *  @brief Return an iterator to the end of the sections
     */
    auto end() { return this->sections().end(); }

    /**
     *  @brief Return an iterator to the start of the sections
     */
    auto begin() const { return this->sections().begin(); }

    /**
     *  @brief Return an iterator to the end of the sections
     */
    auto end() const { return this->sections().end(); }

    /**
     *  @brief Return whether or not the file contains a section with the given
     *         MT number
     */
    bool hasSection( int sectionNo ) const {

      return this->sectionMap.count( sectionNo );
    }

    /**
     *  @brief Return the file number
     */
    static int fileNumber() { return FileNumber; }

    #include "ENDFtk/file/Type/src/section.hpp"
    #include "ENDFtk/file/Type/src/print.hpp"
  };

} // file namespace
} // ENDFtk namespace
} // njoy namespace

#endif
