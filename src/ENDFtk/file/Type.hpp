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

    friend class Base< Type, section::Type< FileNumber > >;
    using Parent = Base< Type, section::Type< FileNumber > >;

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

    using Parent::MF;
    using Parent::sections;
    using Parent::MTs;
    using Parent::begin;
    using Parent::end;
    using Parent::hasMT;
    using Parent::hasSection;
    using Parent::section;
    using Parent::MT;
    using Parent::print;
  };

} // file namespace
} // ENDFtk namespace
} // njoy namespace

#endif
