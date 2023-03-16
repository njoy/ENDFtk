#ifndef NJOY_ENDFTK_FILE_1
#define NJOY_ENDFTK_FILE_1

// system includes
#include <variant>

// other includes
#include "ENDFtk/section/1.hpp"
#include "ENDFtk/file/Base.hpp"
#include "ENDFtk/file/Type.hpp"

namespace njoy {
namespace ENDFtk {
namespace file {

  template<>
  class Type< 1 > : protected Base< Type< 1 >,
                                    std::variant< section::Type< 1, 451 >,
                                                  section::Type< 1, 452 >,
                                                  section::Type< 1, 455 >,
                                                  section::Type< 1, 456 >,
                                                  section::Type< 1, 458 >,
                                                  section::Type< 1, 460 > > > {

    using SectionVariant = std::variant< section::Type< 1, 451 >,
                                         section::Type< 1, 452 >,
                                         section::Type< 1, 455 >,
                                         section::Type< 1, 456 >,
                                         section::Type< 1, 458 >,
                                         section::Type< 1, 460 > >;
    friend class Base< Type, SectionVariant >;

    /* auxiliary functions */
    #include "ENDFtk/file/1/src/getSectionNumber.hpp"
    #include "ENDFtk/file/1/src/printSection.hpp"
    #include "ENDFtk/file/1/src/readSection.hpp"

  public :

    /* ctor */
    #include "ENDFtk/file/1/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the file number
     */
    static constexpr int fileNumber() { return 1; }

    using Base::MF;
    using Base::sections;
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
