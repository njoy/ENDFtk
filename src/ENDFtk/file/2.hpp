#ifndef NJOY_ENDFTK_FILE_2
#define NJOY_ENDFTK_FILE_2

// system includes
#include <variant>

// other includes
#include "ENDFtk/section/2.hpp"
#include "ENDFtk/file/Base.hpp"
#include "ENDFtk/file/Type.hpp"

namespace njoy {
namespace ENDFtk {
namespace file {

  template<>
  class Type< 2 > : protected Base< Type< 2 >,
                                    std::variant< section::Type< 2, 151 >,
                                                  section::Type< 2, 152 > > > {

    using SectionVariant = std::variant< section::Type< 2, 151 >,
                                         section::Type< 2, 152 > >;
    friend class Base< Type, SectionVariant >;

    /* auxiliary functions blatantly copied from MF1 */
    #include "ENDFtk/file/1/src/getSectionNumber.hpp"
    #include "ENDFtk/file/1/src/printSection.hpp"

    /* auxiliary functions */
    #include "ENDFtk/file/2/src/readSection.hpp"

  public :

    /* ctor */
    #include "ENDFtk/file/2/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the file number
     */
    static constexpr int fileNumber() { return 2; }

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
