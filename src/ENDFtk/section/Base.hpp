#ifndef NJOY_ENDFTK_SECTION_BASE
#define NJOY_ENDFTK_SECTION_BASE

// system includes

// other includes
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/section/BaseWithoutMT.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  class Base : public BaseWithoutMT< Base > {

    /* fields */
    int MT_;

  protected:

    /* constructor */
    #include "ENDFtk/section/Base/src/ctor.hpp"

  public:

    /* get methods */
    int sectionNumber() const { return this->MT_; }
    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::targetIdentifier;
    using BaseWithoutMT::AWR;
    using BaseWithoutMT::atomicWeightRatio;
    using BaseWithoutMT::readSEND;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
