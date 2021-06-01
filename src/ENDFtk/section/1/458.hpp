#ifndef NJOY_ENDFTK_SECTION_1_458
#define NJOY_ENDFTK_SECTION_1_458

// system includes
#include <variant>
#include <optional>

// other includes
#include "ENDFtk/types.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/section.hpp"
#include "range/v3/view/chunk.hpp"
#include "range/v3/view/drop_exactly.hpp"
#include "range/v3/view/stride.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief MF1 MT458 - energy release from fission
   *
   *  See ENDF102, section 1.5 for more information.
   */
  template<>
  class Type< 1, 458 > : protected BaseWithoutMT< Type< 1, 458 > > {

    friend BaseWithoutMT< Type< 1, 458 > >;

  public:

    #include "ENDFtk/section/1/458/ThermalPointComponents.hpp"
    #include "ENDFtk/section/1/458/PolynomialComponents.hpp"
    #include "ENDFtk/section/1/458/EnergyReleaseComponent.hpp"
    #include "ENDFtk/section/1/458/TabulatedComponents.hpp"

    using FissionEnergyReleaseData = std::variant< // LFC=0 NPLY=0
                                                   ThermalPointComponents,
                                                   // LFC=0 NPLY!=0
                                                   PolynomialComponents,
                                                   // LFC=1 NPLY=0
                                                   TabulatedComponents >;

  protected:

    /* fields */
    FissionEnergyReleaseData data_;

    /* auxiliary functions */
    #include "ENDFtk/section/1/458/src/readFissionEnergyReleaseData.hpp"

  public:

    /* constructor */
    #include "ENDFtk/section/1/458/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the tabulated energy release flag
     */
    int LFC() const { return std::visit( [] ( const auto& v ) -> long
                                            { return v.LFC(); },
                                         this->data_ ); }

    /**
     *  @brief Return the tabulated energy release flag
     */
    bool tabulatedEnergyRelease() const { return this->LFC(); }

    /**
     *  @brief Return the polynomial expansion order
     */
    int NFC() const { return std::visit( [] ( const auto& v ) -> long
                                            { return v.NFC(); },
                                         this->data_ ); }

    /**
     *  @brief Return the polynomial expansion order
     */
    int order() const { return this->NPLY(); }

    /**
     *  @brief Return the number of tabulated energy release components
     */
    int NPLY() const { return std::visit( [] ( const auto& v ) -> long
                                             { return v.NPLY(); },
                                          this->data_ ); }

    /**
     *  @brief Return the number of tabulated energy release components
     */
    int numberTabulatedComponents() const { return this->NFC(); }

    /**
     *  @brief Return the fission energy release data
     */
    const FissionEnergyReleaseData& energyRelease() const {

      return this->data_;
    }

    /**
     *  @brief Return the number of lines in this MF1/MT458 section
     */
    long NC() const { return 1 + std::visit( [] ( const auto& v ) -> long
                                                { return v.NC(); },
                                             this->data_ ); }

    #include "ENDFtk/section/1/458/src/print.hpp"

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber(){ return 458; }

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::AWR;
    using BaseWithoutMT::atomicWeightRatio;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
