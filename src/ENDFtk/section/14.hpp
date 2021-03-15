#ifndef NJOY_ENDFTK_SECTION_14
#define NJOY_ENDFTK_SECTION_14

// system includes
#include <variant>

// other includes
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief MF14 - angular distributions of secondary photons
   *
   *  See ENDF102, section 14.2 for more information.
   */
  template<>
  class Type< 14 > : protected Base {

  public:

    // #include "ENDFtk/section/4/LegendreCoefficients.hpp"
    // #include "ENDFtk/section/4/TabulatedDistribution.hpp"

    // MF4 Isotropic class is taken over as is in MF14
    #include "ENDFtk/section/4/Isotropic.hpp"                    // LTT=0, LI=1
    // #include "ENDFtk/section/4/LegendreDistributions.hpp"        // LTT=1, LI=0
    // #include "ENDFtk/section/4/TabulatedDistributions.hpp"       // LTT=2, LI=0

    using LTT0 = Isotropic;
    // using LTT1 = LegendreDistributions;
    // using LTT2 = TabulatedDistributions;

    /** @typedef Distributions
     *  @brief The secondary particle angular distribution of MF4
     *
     *  This distribution class is set up as a variant.
     */
    using Distributions = std::variant< Isotropic >; // LTT=0, LI=1

  private:

    /* type aliases */

    /* fields */

    /* auxiliary functions */

  public:

    /* constructor */
    #include "ENDFtk/section/14/src/ctor.hpp"

    /* get methods */

    using Base::MT;
    using Base::sectionNumber;
    using Base::ZA;
    using Base::atomicWeightRatio;
    using Base::AWR;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
