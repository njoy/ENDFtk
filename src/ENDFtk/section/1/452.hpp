#ifndef NJOY_ENDFTK_SECTION_1_452
#define NJOY_ENDFTK_SECTION_1_452

// system includes

// other includes
#include "ENDFtk/types.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/section.hpp"

#include "ENDFtk/nubar.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  template<>
  class Type< 1, 452 > : protected Base {
  protected:

    /* fields */
    nubar::NubarData data_;

  public:

    /* constructor */
  #include "ENDFtk/section/1/452/src/ctor.hpp"

    /* set methods */

    /* get methods */
    virtual int MT() const { return 452; }
    int sectionNumber() const { return this->MT(); }

    int LNU() const { return std::visit( [] ( const auto& v ) -> int
                                            { return v.LNU(); },
                                         this->data_ ); }

    const nubar::NubarData& nubar() const { return this->data_; }

    long NC() const { return 1 + std::visit( [] ( const auto& v ) -> long
                                                { return v.NC(); },
                                             this->data_ ); }

  #include "ENDFtk/section/1/452/src/print.hpp"

    using Base::ZA;
    using Base::AWR;
    using Base::atomicWeightRatio;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
