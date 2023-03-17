#ifndef NJOY_ENDFTK_FILE_8
#define NJOY_ENDFTK_FILE_8

// system includes
#include <variant>

// other includes
#include "ENDFtk/section/8.hpp"
#include "ENDFtk/file/Base.hpp"
#include "ENDFtk/file/Type.hpp"

namespace njoy {
namespace ENDFtk {
namespace file {

  template<>
  class Type< 8 > : protected Base< Type< 8 >,
                                    std::variant< section::Type< 8, 454 >,
                                                  section::Type< 8, 457 >,
                                                  section::Type< 8, 459 > > > {

    using SectionVariant = std::variant< section::Type< 8, 454 >,
                                         section::Type< 8, 457 >,
                                         section::Type< 8, 459 > >;
    friend class Base< Type, SectionVariant >;

    //! @todo remove this
    using Text = record::Base< record::Character< 66 > >;
    using Tail = record::Tail;

    /* auxiliary functions blatantly copied from MF1 */
    #include "ENDFtk/file/1/src/getSectionNumber.hpp"
    #include "ENDFtk/file/1/src/printSection.hpp"

    /* auxiliary functions */
    #include "ENDFtk/file/8/src/readSection.hpp"

  public :

    /* ctor */
    #include "ENDFtk/file/8/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the file number
     */
    static constexpr int fileNumber() { return 8; }

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
