#ifndef NJOY_ENDFTK_SECTION_1_456
#define NJOY_ENDFTK_SECTION_1_456

// system includes

// other includes
#include "ENDFtk/section/1/452.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  template<>
  class Type< 1, 456 > : protected Type< 1, 452 > {

  public:

    /* constructor */
    using Type< 1, 452 >::Type;

    /* get methods */
    static constexpr int sectionNumber(){ return 456; }
    int MT() const { return Type< 1, 456 >::sectionNumber(); }
    using Type< 1, 452 >::LNU;
    using Type< 1, 452 >::nubar;
    using Type< 1, 452 >::NC;
    #include "ENDFtk/section/1/456/src/print.hpp"
    using Type< 1, 452 >::ZA;
    using Type< 1, 452 >::AWR;
    using Type< 1, 452 >::atomicWeightRatio;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
