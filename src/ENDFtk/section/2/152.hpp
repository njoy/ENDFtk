#ifndef NJOY_ENDFTK_SECTION_2_152
#define NJOY_ENDFTK_SECTION_2_152

// system includes
#include <variant>

// other includes
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"
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

    /* workaround for the removal of range-v3 */

    // using transform with more ranges operations in the transform causes issues
    // on the Python side. we just generate the underlying array at construction
    // time to solve it.
    using Iterator = njoy::tools::std20::ranges::iterator_t< decltype( data_.list() ) >;
    using Array = njoy::tools::std20::subrange< Iterator, Iterator >;
    std::vector< std::vector< Array > > reactions_;
    #include "ENDFtk/section/2/152/src/generateArrays.hpp"

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
     *  @brief Return the number of data values
     */
    int numberValues() const { return this->NW(); }

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

      using namespace njoy::tools;
      return this->data_.list() | std20::views::take( this->NSIGZ() );
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

      using namespace njoy::tools;
      return this->data_.list()
               | std20::views::drop( this->NSIGZ() )
               | std23::views::stride( 1 + this->NSIGZ() * 5 );
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
    auto total() const {

      using namespace njoy::tools;
      return std20::views::all( this->reactions_[0] );
    }

    /**
     *  @brief Return the elastic cross section values for each energy and dilution
     */
    auto elastic() const {

      using namespace njoy::tools;
      return std20::views::all( this->reactions_[1] );
    }

    /**
     *  @brief Return the fission cross section values for each energy and dilution
     */
    auto fission() const {

      using namespace njoy::tools;
      return std20::views::all( this->reactions_[2] );
    }

    /**
     *  @brief Return the capture cross section values for each energy and dilution
     */
    auto capture() const {

      using namespace njoy::tools;
      return std20::views::all( this->reactions_[3] );
    }

    /**
     *  @brief Return the current weighted cross section values for each
     *         energy and dilution
     */
    auto currentWeightedTotal() const {

      using namespace njoy::tools;
      return std20::views::all( this->reactions_[4] );
    }

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
