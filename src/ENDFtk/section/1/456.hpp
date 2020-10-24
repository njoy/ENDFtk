#ifndef NJOY_ENDFTK_SECTION_1_456
#define NJOY_ENDFTK_SECTION_1_456

// system includes

// other includes
#include "ENDFtk/section/1/455.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  template<>
  class Type< 1, 456 > : protected Type< 1, 452 > {

  public:

    /* constructor */
    using Type< 1, 452 >::Type;

    /* get methods */
    int MT() const { return 456; }
    using Type< 1, 452 >::sectionNumber;
    using Type< 1, 452 >::LNU;
    using Type< 1, 452 >::nubar;
    using Type< 1, 452 >::NC;
    using Type< 1, 452 >::print;
    using Type< 1, 452 >::ZA;
    using Type< 1, 452 >::AWR;
    using Type< 1, 452 >::atomicWeightRatio;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
