#ifndef NJOY_ENDFTK_SECTION_2_153
#define NJOY_ENDFTK_SECTION_2_153

// system includes

// other includes
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF2 MT153 - unimplemented
   */
  template<>
  class Type< 2, 153 > : protected NotImplementedYet< Type< 2, 153 > > {

    friend NotImplementedYet< Type< 2, 153 > >;

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
    static constexpr int fileNumber(){ return 2; }

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber(){ return 153; }

    using NotImplementedYet::MF;
    using NotImplementedYet::MT;
    using NotImplementedYet::print;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
