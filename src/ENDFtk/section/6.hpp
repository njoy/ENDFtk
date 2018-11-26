template<>
class Type< 6 > : protected Base {

public:

  #include "ENDFtk/section/6/Multiplicity.hpp"

  #include "ENDFtk/section/6/NoLawDataGiven.hpp"
  #include "ENDFtk/section/6/DefinedElsewhere.hpp"                 // LAW<0
  #include "ENDFtk/section/6/Unknown.hpp"                          // LAW=0
  #include "ENDFtk/section/6/ContinuumEnergyAngle.hpp"             // LAW=1
  #include "ENDFtk/section/6/DiscreteTwoBodyScattering.hpp"        // LAW=2
  #include "ENDFtk/section/6/IsotropicDiscreteEmission.hpp"        // LAW=3
  #include "ENDFtk/section/6/DiscreteTwoBodyRecoils.hpp"           // LAW=4
  #include "ENDFtk/section/6/ChargedParticleElasticScattering.hpp" // LAW=5
  #include "ENDFtk/section/6/NBodyPhaseSpace.hpp"                  // LAW=6
  #include "ENDFtk/section/6/LaboratoryAngleEnergy.hpp"            // LAW=7

  using LAW0 = Unknown;
  using LAW1 = ContinuumEnergyAngle;
  using LAW2 = DiscreteTwoBodyScattering;
  using LAW3 = IsotropicDiscreteEmission;
  using LAW4 = DiscreteTwoBodyRecoils;
  using LAW5 = ChargedParticleElasticScattering;
  using LAW6 = NBodyPhaseSpace;
  using LAW7 = LaboratoryAngleEnergy;

  using Distribution = std::variant< // LAW<0
                                     DefinedElsewhere,
                                     // LAW=0
                                     Unknown,
                                     // LAW=1
                                     ContinuumEnergyAngle,
                                     // LAW=2
                                     DiscreteTwoBodyScattering,
                                     // LAW=3
                                     IsotropicDiscreteEmission,
                                     // LAW=4
                                     DiscreteTwoBodyRecoils,
                                     // LAW=5
                                     ChargedParticleElasticScattering,
                                     // LAW=6
                                     NBodyPhaseSpace,
                                     // LAW=7
                                     LaboratoryAngleEnergy >;

  #include "ENDFtk/section/6/ReactionProduct.hpp"

private:

  /* fields */
  int jp_;
  int lct_;
  std::vector< ReactionProduct > products_;

  /* auxiliary functions */
  #include "ENDFtk/section/6/src/readReactionProducts.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/6/src/ctor.hpp"

  /* get methods */
  int JP() const { return this->jp_; }
  int LCT() const { return this->lct_; }
  int NK() const { return this->products_.size(); }

  auto products() const { return ranges::view::all( this->products_ ); }

  #include "ENDFtk/section/6/src/NC.hpp"

  #include "ENDFtk/section/6/src/print.hpp"

  using Base::MT;
  using Base::ZA;
  using Base::atomicWeightRatio;
  using Base::AWR;
};

