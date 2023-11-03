#ifndef NJOY_ENDFTK_SECTION_32_151
#define NJOY_ENDFTK_SECTION_32_151

// system includes
#include <optional>
#include <variant>

// other includes
#include "range/v3/range/conversion.hpp"
#include "range/v3/view/chunk.hpp"
#include "range/v3/view/concat.hpp"
#include "range/v3/view/drop_exactly.hpp"
#include "range/v3/view/stride.hpp"
#include "range/v3/view/take_exactly.hpp"
#include "range/v3/view/transform.hpp"
#include "ENDFtk/record.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section/covariance.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF32 MT151 - resonance parameters
   *
   *  See ENDF102, section 32.1 for more information.
   */
  template<>
  class Type< 32, 151 > : protected BaseWithoutMT< Type< 32, 151 > > {

  public:

    #include "ENDFtk/section/32/151/ScatteringRadiusCovariances.hpp"

    // LCOMP = 0 components
    #include "ENDFtk/section/32/151/LimitedBreitWignerLValue.hpp"
    #include "ENDFtk/section/32/151/LimitedCovarianceBase.hpp"
    #include "ENDFtk/section/32/151/LimitedSingleLevelBreitWigner.hpp"
    #include "ENDFtk/section/32/151/LimitedMultiLevelBreitWigner.hpp"

    // LCOMP = 1 components
    #include "ENDFtk/section/32/151/ShortRangeBreitWignerReichMooreBlockBase.hpp"
    #include "ENDFtk/section/32/151/ShortRangeBreitWignerBlock.hpp"
    #include "ENDFtk/section/32/151/ShortRangeReichMooreBlock.hpp"
    #include "ENDFtk/section/32/151/ShortRangeRMatrixLimitedBlock.hpp"
    #include "ENDFtk/section/32/151/ReichMooreScatteringRadiusUncertainties.hpp"
    //! @todo add LB=-1 to Covariancepairs
    //! @todo add LRF=7 scattering radius uncertainties
    using LongRangeCovarianceBlock = std::variant< CovariancePairs, SquareMatrix >;
    #include "ENDFtk/section/32/151/GeneralCovarianceBase.hpp"
    #include "ENDFtk/section/32/151/GeneralSingleLevelBreitWigner.hpp"
    #include "ENDFtk/section/32/151/GeneralMultiLevelBreitWigner.hpp"
    #include "ENDFtk/section/32/151/GeneralReichMoore.hpp"
    #include "ENDFtk/section/32/151/GeneralRMatrixLimited.hpp"

    // LCOMP = 2 components
    #include "ENDFtk/section/32/151/CompactCorrelationMatrix.hpp"

    #include "ENDFtk/section/32/151/ResonanceRange.hpp"
    #include "ENDFtk/section/32/151/Isotope.hpp"

  private:

    friend BaseWithoutMT< Type< 32, 151 > >;

    /* fields */
    std::vector< Isotope > isotopes_;

    /* auxiliary functions */
    #include "ENDFtk/section/2/151/src/verifyNIS.hpp"

  public:

    /* constructor */
    #include "ENDFtk/section/32/151/src/ctor.hpp"

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber() { return 151; }

    /**
     *  @brief Return the number NIS of isotopes
     */
    unsigned int numberIsotopes() const { return this->NIS(); }

    /**
     *  @brief Return the number NIS of isotopes
     */
    unsigned int NIS() const { return this->isotopes_.size(); }

    /**
     *  @brief Return the isotopes defined in the section
     */
    auto isotopes() const {

      return ranges::cpp20::views::all( this->isotopes_ );
    }

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::atomicWeightRatio;
    using BaseWithoutMT::AWR;

    #include "ENDFtk/section/32/151/src/print.hpp"
    #include "ENDFtk/section/32/151/src/NC.hpp"
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
