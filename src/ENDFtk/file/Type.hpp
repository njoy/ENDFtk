#ifndef NJOY_ENDFTK_FILE_TYPE
#define NJOY_ENDFTK_FILE_TYPE

// system includes

// other includes
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
  class Type : protected Base< Type< FileNumber >, section::Type< FileNumber > > {

    friend class Base< Type< FileNumber >, section::Type< FileNumber > >;

    /* auxiliary functions */
    #include "ENDFtk/file/Type/src/getSectionNumber.hpp"
    #include "ENDFtk/file/Type/src/printSection.hpp"
    #include "ENDFtk/file/Type/src/readSection.hpp"

  public :

    /* constructors */
    #include "ENDFtk/file/Type/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the file number
     */
    static int fileNumber() { return FileNumber; }

    using Base< Type< FileNumber >, section::Type< FileNumber > >::MF;
    using Base< Type< FileNumber >, section::Type< FileNumber > >::sections;
    using Base< Type< FileNumber >, section::Type< FileNumber > >::begin;
    using Base< Type< FileNumber >, section::Type< FileNumber > >::end;
    using Base< Type< FileNumber >, section::Type< FileNumber > >::hasMT;
    using Base< Type< FileNumber >, section::Type< FileNumber > >::hasSection;
    using Base< Type< FileNumber >, section::Type< FileNumber > >::section;
    using Base< Type< FileNumber >, section::Type< FileNumber > >::MT;
    using Base< Type< FileNumber >, section::Type< FileNumber > >::print;
  };

} // file namespace
} // ENDFtk namespace
} // njoy namespace

#endif
