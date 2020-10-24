#ifndef NJOY_ENDFTK_SECTION_1_455
#define NJOY_ENDFTK_SECTION_1_455

// system includes

// other includes
#include "ENDFtk/types.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/section/1/452.hpp"

#include "ENDFtk/nubar.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  template<>
  class Type< 1, 455 > : protected Base {
  protected:

    /* fields */
    nubar::DecayConstantData lambda_;
    nubar::NubarData nubar_;

  public:

    /* constructor */
  #include "ENDFtk/section/1/455/src/ctor.hpp"

    /* set methods */

    /* get methods */
    static constexpr int MT() { return 455; }
    static constexpr int sectionNumber() { return MT(); }

    int LNU() const { return std::visit( [] ( const auto& v ) -> long
                                            { return v.LNU(); },
                                         this->nubar_ ); }

    int LDG() const { return std::visit( [] ( const auto& v ) -> long
                                            { return v.LDG(); },
                                         this->lambda_ ); }

    const nubar::DecayConstantData& lambda() const { return this->lambda_; }

    const nubar::NubarData& nubar() const { return this->nubar_; }

    long NC() const { return 1 + std::visit( [] ( const auto& v ) -> long
                                                { return v.NC(); },
                                             this->lambda_ )
                               + std::visit( [] ( const auto& v ) -> long
                                                { return v.NC(); },
                                             this->nubar_ ); }

  #include "ENDFtk/section/1/455/src/print.hpp"

    using Base::ZA;
    using Base::AWR;
    using Base::atomicWeightRatio;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
