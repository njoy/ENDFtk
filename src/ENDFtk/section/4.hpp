#ifndef NJOY_ENDFTK_SECTION_4
#define NJOY_ENDFTK_SECTION_4

// system includes
#include <variant>
#include <vector>

// other includes
#include "range/v3/view/concat.hpp"
#include "range/v3/view/transform.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/InterpolationSequenceRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief MF4 - angular distributions of secondary particles
   *
   *  See ENDF102, section 4.2 for more information.
   */
  template<>
  class Type< 4 > : protected Base {

  protected:

    #include "ENDFtk/section/4/AngularDistributions.hpp"

  public:

    #include "ENDFtk/section/4/LegendreCoefficients.hpp"
    #include "ENDFtk/section/4/TabulatedDistribution.hpp"

    #include "ENDFtk/section/4/Isotropic.hpp"                    // LTT=0, LI=1
    #include "ENDFtk/section/4/LegendreDistributions.hpp"        // LTT=1, LI=0
    #include "ENDFtk/section/4/TabulatedDistributions.hpp"       // LTT=2, LI=0
    #include "ENDFtk/section/4/MixedDistributions.hpp"           // LTT=3, LI=0

    using LTT0 = Isotropic;
    using LTT1 = LegendreDistributions;
    using LTT2 = TabulatedDistributions;
    using LTT3 = MixedDistributions;

    /** @typedef Distributions
     *  @brief The secondary particle angular distribution of MF4
     *
     *  This distribution class is set up as a variant.
     */
    using Distributions =
              std::variant< Isotropic,                           // LTT=0, LI=1
                            LegendreDistributions,               // LTT=1, LI=0
                            TabulatedDistributions,              // LTT=2, LI=0
                            MixedDistributions >;                // LTT=3, LI=0

  private:

    /* fields */
    int lct_;
    Distributions distributions_;

    /* auxiliary functions */
    #include "ENDFtk/section/4/src/readDistributions.hpp"

  public:

    /* constructor */
    #include "ENDFtk/section/4/src/ctor.hpp"

    /* get methods */

    /**
     *  @brief Return the reference frame
     */
    int LCT() const { return this->lct_; }

    /**
     *  @brief Return the reference frame
     */
    int referenceFrame() const { return this->LCT(); }

    /**
     *  @brief Return the distribution law
     */
    int LTT() const { return this->distributions_.index(); }

    /**
     *  @brief Return the distribution law
     */
    int LAW() const { return this->LTT(); }

    /**
     *  @brief Return the isotropic angular distribution flag
     */
    bool LI() const { return this->LTT() == 0; }

    /**
     *  @brief Return the isotropic angular distribution flag
     */
    bool isotropicAngularDistributions() const { return this->LI(); }

    /**
     *  @brief Return the partial distributions defined in this section
     */
    const auto& distributions() const { return this->distributions_; }

    #include "ENDFtk/section/4/src/NC.hpp"
    #include "ENDFtk/section/4/src/print.hpp"

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
