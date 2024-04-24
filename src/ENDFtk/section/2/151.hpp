#ifndef NJOY_ENDFTK_SECTION_2_151
#define NJOY_ENDFTK_SECTION_2_151

// system includes
#include <complex>
#include <variant>
#include <optional>

// other includes
#include "range/v3/algorithm/count.hpp"
#include "range/v3/algorithm/find.hpp"
#include "range/v3/range/conversion.hpp"
#include "range/v3/view/all.hpp"
#include "range/v3/view/iota.hpp"
#include "range/v3/view/transform.hpp"
#include "range/v3/view/chunk.hpp"
#include "range/v3/view/drop_exactly.hpp"
#include "range/v3/view/repeat_n.hpp"
#include "range/v3/view/stride.hpp"
#include "range/v3/view/zip_with.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/readSequence.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF2 MT151 - resonance parameters
   *
   *  See ENDF102, section 2.1 for more information.
   */
  template<>
  class Type< 2, 151 > : protected BaseWithoutMT< Type< 2, 151 > > {

  public:

    #include "ENDFtk/section/2/151/BreitWignerReichMooreBase.hpp"
    #include "ENDFtk/section/2/151/BreitWignerReichMooreLValueBase.hpp"

    #include "ENDFtk/section/2/151/UnresolvedLValueBase.hpp"
    #include "ENDFtk/section/2/151/UnresolvedBaseWithoutSpin.hpp"
    #include "ENDFtk/section/2/151/UnresolvedBase.hpp"

    #include "ENDFtk/section/2/151/BreitWignerLValue.hpp"
    #include "ENDFtk/section/2/151/ReichMooreLValue.hpp"

    #include "ENDFtk/section/2/151/SpecialCase.hpp"

    #include "ENDFtk/section/2/151/SingleLevelBreitWigner.hpp"
    #include "ENDFtk/section/2/151/MultiLevelBreitWigner.hpp"
    #include "ENDFtk/section/2/151/ReichMoore.hpp"
    #include "ENDFtk/section/2/151/RMatrixLimited.hpp"

    using SLBW = SingleLevelBreitWigner;
    using MLBW = MultiLevelBreitWigner;
    using RM = ReichMoore;
    using RML = RMatrixLimited;

    #include "ENDFtk/section/2/151/UnresolvedEnergyIndependent.hpp"
    #include "ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths.hpp"
    #include "ENDFtk/section/2/151/UnresolvedEnergyDependent.hpp"

    using CaseA = UnresolvedEnergyIndependent;
    using CaseB = UnresolvedEnergyDependentFissionWidths;
    using CaseC = UnresolvedEnergyDependent;

    #include "ENDFtk/section/2/151/ScatteringRadius.hpp"
    #include "ENDFtk/section/2/151/ResonanceRange.hpp"
    #include "ENDFtk/section/2/151/Isotope.hpp"

  private:

    friend BaseWithoutMT< Type< 2, 151 > >;

    /* fields */
    std::vector< Isotope > isotopes_;

    /* auxiliary functions */
    #include "ENDFtk/section/2/151/src/verifyNIS.hpp"

  public:

    /* constructor */
    #include "ENDFtk/section/2/151/src/ctor.hpp"

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
    using BaseWithoutMT::targetIdentifier;
    using BaseWithoutMT::atomicWeightRatio;
    using BaseWithoutMT::AWR;

    #include "ENDFtk/section/2/151/src/print.hpp"
    #include "ENDFtk/section/2/151/src/NC.hpp"
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
