#ifndef NJOY_ENDFTK_SECTION_1_456
#define NJOY_ENDFTK_SECTION_1_456

// system includes
#include <variant>

// other includes
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/section.hpp"

#include "ENDFtk/section/1/PolynomialMultiplicity.hpp"
#include "ENDFtk/section/1/TabulatedMultiplicity.hpp"
#include "ENDFtk/section/1/readMultiplicity.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF1 MT456 - the number of prompt fission neutrons
   *
   *  This section is essentially identical to MF1 MT452 so we could have
   *  inherited from that section but the reference_wrapper in the
   *  ENDFtk.MF1.File python bindings does not seem to handle it.
   *
   *  See ENDF102, section 1.4 for more information.
   */
  template<>
  class Type< 1, 456 > : protected BaseWithoutMT< Type< 1, 456 > > {

    friend BaseWithoutMT< Type< 1, 456 > >;

  public:

    using Multiplicity = std::variant< PolynomialMultiplicity,  // LNU=1
                                       TabulatedMultiplicity >; // LNU=2

  private:

    /* fields */
    Multiplicity data_;

  public:

    /* constructors */
    #include "ENDFtk/section/1/456/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the fission multiplicity representation type
     */
    int LNU() const { return std::visit( [] ( const auto& v ) -> int
                                            { return v.LNU(); },
                                         this->data_ ); }

    /**
     *  @brief Return the fission multiplicity representation type
     */
    int representation() const { return this->LNU(); }

    /**
     *  @brief Return the fission multiplicity data
     */
    const Multiplicity& nubar() const { return this->data_; }

    /**
     *  @brief Return the number of lines in this MF1/MT456 section
     */
    long NC() const { return 1 + std::visit( [] ( const auto& v ) -> long
                                                { return v.NC(); },
                                             this->data_ ); }

    #include "ENDFtk/section/1/456/src/print.hpp"

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber(){ return 456; }

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::targetIdentifier;
    using BaseWithoutMT::AWR;
    using BaseWithoutMT::atomicWeightRatio;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
