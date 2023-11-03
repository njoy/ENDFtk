#ifndef NJOY_ENDFTK_FILE_32
#define NJOY_ENDFTK_FILE_32

// system includes

// other includes
#include "ENDFtk/section/32.hpp"
#include "ENDFtk/file/Base.hpp"
#include "ENDFtk/file/Type.hpp"

namespace njoy {
namespace ENDFtk {
namespace file {

  template<>
  class Type< 32 > : protected Base< Type< 32 >, section::Type< 32, 151 > > {

    friend class Base< Type, section::Type< 32, 151 > >;

    /* auxiliary functions */
    #include "ENDFtk/file/32/src/getSectionNumber.hpp"
    #include "ENDFtk/file/32/src/printSection.hpp"
    #include "ENDFtk/file/32/src/readSection.hpp"

  public :

    /* ctor */
    #include "ENDFtk/file/32/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the file number
     */
    static constexpr int fileNumber() { return 32; }

    using Base::MF;
    using Base::sections;
    using Base::MTs;
    using Base::begin;
    using Base::end;
    using Base::hasMT;
    using Base::hasSection;
    using Base::section;
    using Base::MT;
    using Base::print;
  };

} // file namespace
} // ENDFtk namespace
} // njoy namespace

#endif
