#ifndef NJOY_ENDFTK_SECTION_8_459
#define NJOY_ENDFTK_SECTION_8_459

// system includes

// other includes
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF8 MT459 - unimplemented
   */
  template<>
  class Type< 8, 459 > : protected NotImplementedYet< Type< 8, 459 > > {

    friend NotImplementedYet< Type< 8, 459 > >;

  public:

    Type() : NotImplementedYet() {}
    template< typename Iterator >
    Type( HEAD& head, Iterator& begin, const Iterator& end,
          long& lineNumber, int MAT ) :
      NotImplementedYet( head, begin, end,
                         lineNumber, MAT ) {}

    /**
     *  @brief Return the MF number of the section
     */
    static constexpr int fileNumber(){ return 8; }

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber(){ return 459; }

    using NotImplementedYet::MF;
    using NotImplementedYet::MT;
    using NotImplementedYet::print;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
