#ifndef NJOY_ENDFTK_SECTION_1_452
#define NJOY_ENDFTK_SECTION_1_452

// system includes
#include <variant>

// other includes
#include "ENDFtk/types.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/section.hpp"

#include "ENDFtk/section/1/PolynomialMultiplicity.hpp"
#include "ENDFtk/section/1/TabulatedMultiplicity.hpp"
#include "ENDFtk/section/1/readNubarData.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  template<>
  class Type< 1, 452 > : protected BaseWithoutMT< Type< 1, 452 > > {

    friend BaseWithoutMT< Type< 1, 452 > >;

  public:

    using NubarData = std::variant< Polynomial,              // LNU=1
                                    TabulatedMultiplicity >; // LNU=2

  private:

    /* fields */
    NubarData data_;

  public:

    /* constructor */
  #include "ENDFtk/section/1/452/src/ctor.hpp"

    /* set methods */

    /* get methods */

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber(){ return 452; }

    int LNU() const { return std::visit( [] ( const auto& v ) -> int
                                            { return v.LNU(); },
                                         this->data_ ); }

    const NubarData& nubar() const { return this->data_; }

    long NC() const { return 1 + std::visit( [] ( const auto& v ) -> long
                                                { return v.NC(); },
                                             this->data_ ); }

    #include "ENDFtk/section/1/452/src/print.hpp"

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::AWR;
    using BaseWithoutMT::atomicWeightRatio;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
