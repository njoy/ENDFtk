#ifndef NJOY_ENDFTK_SECTION_7_4
#define NJOY_ENDFTK_SECTION_7_4

// system includes
#include <variant>
#include <optional>
#include <vector>
#include <optional>

// other includes
#include "range/v3/algorithm/find.hpp"
#include "range/v3/view/all.hpp"
#include "range/v3/view/concat.hpp"
#include "range/v3/view/drop_exactly.hpp"
#include "range/v3/view/single.hpp"
#include "range/v3/view/stride.hpp"
#include "range/v3/view/transform.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/InterpolationSequenceRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  template<>
  class ENDFTK_PYTHON_EXPORT Type< 7, 4 > : 
    protected BaseWithoutMT< Type< 7, 4 > > {

    friend BaseWithoutMT< Type< 7, 4 > >;

  public:

    #include "ENDFtk/section/7/4/ScatteringLawConstants.hpp"

    #include "ENDFtk/section/7/4/AnalyticalFunctions.hpp"
    #include "ENDFtk/section/7/4/TabulatedFunctions.hpp"

    #include "ENDFtk/section/7/4/EffectiveTemperature.hpp"

    /** @typedef ScatteringLaw
     *  @brief The incoherent inelastic scattering law of MF7/MT4
     *
     *  This scattering law class is set up as a variant because the incoherent
     *  inelastic scattering law in MF7/MT4 can either be a given as analytical
     *  functions or as a tabulated S(a,b) function.
     */
    using ScatteringLaw = std::variant< // B(1)=0
                                        AnalyticalFunctions,
                                        // B(1)!=0
                                        TabulatedFunctions >;

    /* type aliases */
    using OptionalEffectiveTemperature = std::optional< EffectiveTemperature >;

  private:

    /* fields */
    int lat_;
    int lasym_;

    ScatteringLawConstants b_;
    ScatteringLaw law_;

    EffectiveTemperature principal_;
    std::vector< OptionalEffectiveTemperature > secondary_;

    /* auxiliary functions */
    #include "ENDFtk/section/7/4/src/readSecondaryTemperatures.hpp"
    #include "ENDFtk/section/7/4/src/readScatteringLaw.hpp"
    #include "ENDFtk/section/7/4/src/checkValue.hpp"
    #include "ENDFtk/section/7/4/src/verifySecondaryTemperatures.hpp"

  public:

    /* constructor */
    #include "ENDFtk/section/7/4/src/ctor.hpp"

    /* get methods */

    /**
     *  @brief Return the LAT flag (temperature flag for alpha and beta grid)
     */
    int LAT() const { return this->lat_; }

    /**
     *  @brief Return the LAT flag (temperature flag for alpha and beta grid)
     */
    int temperatureOption() const { return this->LAT(); }

    /**
     *  @brief Return the LASYM flag (S(alpha,beta) is symmetric or not)
     */
    int LASYM() const { return this->lasym_; }

    /**
     *  @brief Return the LASYM flag (S(alpha,beta) is symmetric or not)
     */
    int symmetryOption() const { return this->LASYM(); }

    /**
     *  @brief Return the thermal scattering law constants for the principal and
     *         and secondary scatterers (if any)
     */
    const ScatteringLawConstants& constants() const { return this->b_; }

    /**
     *  @brief Return the thermal scattering law (either analytical or tabulated)
     */
    const ScatteringLaw& scatteringLaw() const { return this->law_; }

    /**
     *  @brief Return the effective temperature for the principal scatterer
     */
    const EffectiveTemperature& principalEffectiveTemperature() const {

      return this->principal_;
    }

    /**
     *  @brief Return the effective temperatures for the secondary scatterers
     *         (if any are defined)
     */
    auto secondaryEffectiveTemperatures() const {

      return ranges::cpp20::views::all( this->secondary_ );
    }

    #include "ENDFtk/section/7/4/src/NC.hpp"
    #include "ENDFtk/section/7/4/src/print.hpp"

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber() { return 4; }

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
