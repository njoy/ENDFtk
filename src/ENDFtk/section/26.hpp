#ifndef NJOY_ENDFTK_SECTION_26
#define NJOY_ENDFTK_SECTION_26

// system includes

// other includes
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
   *  @brief 26 - secondary distributions for photo- and electro-atomic interactions
   *
   *  See ENDF102, section 26.2 for more information.
   */
  template<>
  class Type< 26 > : protected Base {

  public:

    #include "ENDFtk/section/26/Multiplicity.hpp"

//    #include "ENDFtk/section/6/NoLawDataGiven.hpp"
//    #include "ENDFtk/section/6/DefinedElsewhere.hpp"                 // LAW<0
//    #include "ENDFtk/section/6/Unknown.hpp"                          // LAW=0
//    #include "ENDFtk/section/6/ContinuumEnergyAngle.hpp"             // LAW=1
//    #include "ENDFtk/section/6/DiscreteTwoBodyScattering.hpp"        // LAW=2
//    #include "ENDFtk/section/6/IsotropicDiscreteEmission.hpp"        // LAW=3
//    #include "ENDFtk/section/6/DiscreteTwoBodyRecoils.hpp"           // LAW=4
//    #include "ENDFtk/section/6/ChargedParticleElasticScattering.hpp" // LAW=5
//    #include "ENDFtk/section/6/NBodyPhaseSpace.hpp"                  // LAW=6
//    #include "ENDFtk/section/6/LaboratoryAngleEnergy.hpp"            // LAW=7
//
//    using LAW0 = Unknown;
//    using LAW1 = ContinuumEnergyAngle;
//    using LAW2 = DiscreteTwoBodyScattering;
//    using LAW3 = IsotropicDiscreteEmission;
//    using LAW4 = DiscreteTwoBodyRecoils;
//    using LAW5 = ChargedParticleElasticScattering;
//    using LAW6 = NBodyPhaseSpace;
//    using LAW7 = LaboratoryAngleEnergy;
//
//    using Distribution = std::variant< DefinedElsewhere,                 // LAW<0
//                                       Unknown,                          // LAW=0
//                                       ContinuumEnergyAngle,             // LAW=1
//                                       DiscreteTwoBodyScattering,        // LAW=2
//                                       IsotropicDiscreteEmission,        // LAW=3
//                                       DiscreteTwoBodyRecoils,           // LAW=4
//                                       ChargedParticleElasticScattering, // LAW=5
//                                       NBodyPhaseSpace,                  // LAW=6
//                                       LaboratoryAngleEnergy >;          // LAW=7
//
//    #include "ENDFtk/section/6/ReactionProduct.hpp"

  private:

    /* fields */
//    std::vector< ReactionProduct > products_;

    /* auxiliary functions */

  public:

    /* constructor */
    #include "ENDFtk/section/26/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the number of reaction products
     */
//    int NK() const { return this->products_.size(); }

    /**
     *  @brief Return the number of reaction products
     */
//    int numberReactionProducts() const { return this->NK(); }

    /**
     *  @brief Return the reaction products defined in this section
     */
//    auto reactionProducts() const {
//
//      return ranges::cpp20::views::all( this->products_ );
//    }

//    #include "ENDFtk/section/6/src/NC.hpp"
//    #include "ENDFtk/section/6/src/print.hpp"

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
