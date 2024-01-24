#ifndef NJOY_ENDFTK_SECTION_1_455
#define NJOY_ENDFTK_SECTION_1_455

// system includes
#include <variant>

// other includes
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/InterpolationSequenceRecord.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/section.hpp"
#include "range/v3/view/stride.hpp"
#include "range/v3/view/drop_exactly.hpp"

#include "ENDFtk/section/1/PolynomialMultiplicity.hpp"
#include "ENDFtk/section/1/TabulatedMultiplicity.hpp"
#include "ENDFtk/section/1/readMultiplicity.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief MF1 MT455 - the number of delayed fission neutrons
   *
   *  See ENDF102, section 1.3 for more information.
   */
  template<>
  class Type< 1, 455 > : protected BaseWithoutMT< Type< 1, 455 > > {

    friend BaseWithoutMT< Type< 1, 455 > >;

  public:

    #include "ENDFtk/section/1/455/EnergyIndependentConstants.hpp"
    #include "ENDFtk/section/1/455/DecayConstants.hpp"
    #include "ENDFtk/section/1/455/EnergyDependentConstants.hpp"

    using DecayConstantData = std::variant< EnergyIndependentConstants, // LDG=0
                                            EnergyDependentConstants >; // LDG=1

    using Multiplicity = std::variant< PolynomialMultiplicity,  // LNU=1
                                       TabulatedMultiplicity >; // LNU=2

  private:

    /* fields */
    DecayConstantData lambda_;
    Multiplicity nubar_;

    /* auxiliary functions */
    #include "ENDFtk/section/1/455/src/readDecayConstantData.hpp"

  public:

    /* constructor */
    #include "ENDFtk/section/1/455/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the fission multiplicity representation type
     */
    int LNU() const { return std::visit( [] ( const auto& v ) -> long
                                            { return v.LNU(); },
                                         this->nubar_ ); }

    /**
     *  @brief Return the fission multiplicity representation type
     */
    int representation() const { return this->LNU(); }

    /**
     *  @brief Return the type of decay constants
     */
    int LDG() const { return std::visit( [] ( const auto& v ) -> long
                                            { return v.LDG(); },
                                         this->lambda_ ); }

    /**
     *  @brief Return the type of decay constants
     */
    int type() const { return this->LDG(); }

    /**
     *  @brief Return the decay constant data for the delayed precursor groups
     */
    const DecayConstantData& delayedGroups() const { return this->lambda_; }

    /**
     *  @brief Return the fission multiplicity data
     */
    const Multiplicity& nubar() const { return this->nubar_; }

    /**
     *  @brief Return the number of lines in this MF1/MT455 section
     */
    long NC() const { return 1 + std::visit( [] ( const auto& v ) -> long
                                                { return v.NC(); },
                                             this->lambda_ )
                               + std::visit( [] ( const auto& v ) -> long
                                                { return v.NC(); },
                                             this->nubar_ ); }

    #include "ENDFtk/section/1/455/src/print.hpp"

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber(){ return 455; }

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
