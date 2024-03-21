#ifndef NJOY_ENDFTK_SECTION_5
#define NJOY_ENDFTK_SECTION_5

// system includes
#include <variant>
#include <vector>

// other includes
#include "range/v3/view/all.hpp"
#include "range/v3/view/transform.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/InterpolationSequenceRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  template<>
  class ENDFTK_PYTHON_EXPORT Type< 5 > : protected Base {
  
  public:
  
    #include "ENDFtk/section/5/DistributionFunction.hpp"
    #include "ENDFtk/section/5/Parameter.hpp"
    #include "ENDFtk/section/5/EffectiveTemperature.hpp"
  
    #include "ENDFtk/section/5/TabulatedSpectrum.hpp"            // LF=1
    #include "ENDFtk/section/5/GeneralEvaporationSpectrum.hpp"   // LF=5
    #include "ENDFtk/section/5/MaxwellianFissionSpectrum.hpp"    // LF=7
    #include "ENDFtk/section/5/EvaporationSpectrum.hpp"          // LF=9
    #include "ENDFtk/section/5/WattSpectrum.hpp"                 // LF=11
    #include "ENDFtk/section/5/MadlandNixSpectrum.hpp"           // LF=12
  
    using LF1 = TabulatedSpectrum;
    using LF5 = GeneralEvaporationSpectrum;
    using LF7 = MaxwellianFissionSpectrum;
    using LF9 = EvaporationSpectrum;
    using LF11 = WattSpectrum;
    using LF12 = MadlandNixSpectrum;
  
    /** @typedef Distribution
     *  @brief A secondary particle energy distribution of MF5
     */
    using Distribution = std::variant< TabulatedSpectrum,           // LF=1
                                       GeneralEvaporationSpectrum,  // LF=5
                                       MaxwellianFissionSpectrum,   // LF=7
                                       EvaporationSpectrum,         // LF=9
                                       WattSpectrum,                // LF=11
                                       MadlandNixSpectrum >;        // LF=12
    #include "ENDFtk/section/5/Probability.hpp"
  
    #include "ENDFtk/section/5/PartialDistribution.hpp"
  
  private:
  
    /* fields */
    std::vector< PartialDistribution > partials_;
  
    /* auxiliary functions */
    #include "ENDFtk/section/5/src/verifyNK.hpp"
  
  public:
  
    /* constructor */
    #include "ENDFtk/section/5/src/ctor.hpp"
  
    /* methods */
  
    /**
     *  @brief Return the number NK of subsections with partial distributions
     */
    int NK() const { return this->partials_.size(); }
  
    /**
     *  @brief Return the number NK of subsections with partial distributions
     */
    int numberPartialDistributions() const { return this->NK(); }
  
    /**
     *  @brief Return the partial distributions defined in this section
     */
    auto partialDistributions() const {
  
      return ranges::cpp20::views::all( this->partials_ );
    }
  
    #include "ENDFtk/section/5/src/NC.hpp"
    #include "ENDFtk/section/5/src/print.hpp"
  
    using Base::MT;
    using Base::sectionNumber;
    using Base::ZA;
    using Base::targetIdentifier;
    using Base::atomicWeightRatio;
    using Base::AWR;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
