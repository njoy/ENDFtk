#ifndef NJOY_ENDFTK_SECTION_2_152
#define NJOY_ENDFTK_SECTION_2_152

// system includes
#include <variant>

// other includes
#include "range/v3/view/chunk.hpp"
#include "range/v3/view/drop_exactly.hpp"
#include "range/v3/view/stride.hpp"
#include "range/v3/view/take_exactly.hpp"
#include "range/v3/view/transform.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF2 MT152 - internal NJOY section
   *
   *  See the NJOY manual, RECONR and UNRESR for more information.
   */
  template<>
  class Type< 2, 152 > : protected BaseWithoutMT< Type< 2, 152 > > {

    friend BaseWithoutMT< Type< 2, 152 > >;

    /* fields */
    bool lssf_;
    int interpolation_;
    ListRecord data_;

    /* auxiliary functions */
    #include "ENDFtk/section/2/152/src/generateList.hpp"
    #include "ENDFtk/section/2/152/src/reaction.hpp"
    #include "ENDFtk/section/2/152/src/verifySize.hpp"

  public:

    /* constructor */
    #include "ENDFtk/section/2/152/src/ctor.hpp"

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber() { return 152; }

    /**
     *  @brief Return the self-shielding only flag
     */
    bool LSSF() const { return this->lssf_; }

    /**
     *  @brief Return the self-shielding only flag
     */
    bool selfShieldingOnly() const { return this->LSSF(); }

    /**
     *  @brief Return the interpolation flag
     */
    int interpolation() const { return this->interpolation_; }

    /**
     *  @brief Return the temperature
     */
    double TEMZ() const { return this->data_.C1(); }

    /**
     *  @brief Return the temperature
     */
    double temperature() const { return this->TEMZ(); }

    /**
     *  @brief Return the number of data values
     */
    int NW() const { return this->data_.NPL(); }

    /**
     *  @brief Return the number of reactions (normally 5)
     */
    int NREAC() const { return this->data_.L1(); }

    /**
     *  @brief Return the number of reactions (normally 5)
     */
    int numberReactions() const { return this->NREAC(); }

    /**
     *  @brief Return the number of dilution or sigma zero values
     */
    int NSIGZ() const { return this->data_.L2(); }

    /**
     *  @brief Return the number of dilution or sigma zero values
     */
    int numberDilutions() const { return this->NSIGZ(); }

    /**
     *  @brief Return the dilution or sigma zero values
     */
    auto SIGZ() const {

      return this->data_.list()
               | ranges::views::take_exactly( this->NSIGZ() );
    }

    /**
     *  @brief Return the dilution or sigma zero values
     */
    auto dilutions() const { return this->SIGZ(); }

    /**
     *  @brief Return the number of energy values
     */
    int NUNR() const { return this->data_.N2(); }

    /**
     *  @brief Return the number of energy values
     */
    int numberEnergies() const { return this->NUNR(); }

    /**
     *  @brief Return the unresolved resonance energies
     */
    auto EUNR() const {

      return this->data_.list()
               | ranges::views::drop_exactly( this->NSIGZ() )
               | ranges::views::stride( 1 + this->NSIGZ() * 5 );
    }

    /**
     *  @brief Return the unresolved resonance energies
     */
    auto energies() const {

      return this->EUNR();
    }

    /**
     *  @brief Return the total cross section values for each energy and dilution
     */
    auto total() const { return this->reaction( 0 ); }

    /**
     *  @brief Return the elastic cross section values for each energy and dilution
     */
    auto elastic() const { return this->reaction( 1 ); }

    /**
     *  @brief Return the fission cross section values for each energy and dilution
     */
    auto fission() const { return this->reaction( 2 ); }

    /**
     *  @brief Return the capture cross section values for each energy and dilution
     */
    auto capture() const { return this->reaction( 3 ); }

    /**
     *  @brief Return the current weighted cross section values for each
     *         energy and dilution
     */
    auto currentWeightedTotal() const { return this->reaction( 4 ); }

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::targetIdentifier;
    using BaseWithoutMT::atomicWeightRatio;
    using BaseWithoutMT::AWR;

    #include "ENDFtk/section/2/152/src/print.hpp"
    #include "ENDFtk/section/2/152/src/NC.hpp"
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
