class UnresolvedEnergyIndependent;
template < typename GCC >
struct LJValueType< UnresolvedEnergyIndependent, GCC > {

  #include "ENDFtk/section/2/151/UnresolvedEnergyIndependent/JValue.hpp"
  #include "ENDFtk/section/2/151/UnresolvedEnergyIndependent/LValue.hpp"

  template < typename Range > using JType = JValue< Range >;
  using LType = LValue;
};

/**
 *  @class
 *  @brief Single level Breit-Wigner unresolved resonance parameters with
 *         energy independent widths and no fission given
 *
 *  The EnergyIndependentSingleLevelBreitWigner class is used to represent the
 *  SLBW unresolved parameters from MF2/MT151 for LRU=2 LRF=1 LFW=0.
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
class UnresolvedEnergyIndependent :
  public UnresolvedBase< UnresolvedEnergyIndependent > {

public:

  template < typename Range >
  using JValue = LJValueType< UnresolvedEnergyIndependent >::JType< Range >;
  using LValue = LJValueType< UnresolvedEnergyIndependent >::LType;

  /* constructor */
  #include "ENDFtk/section/2/151/UnresolvedEnergyIndependent/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int LRU() { return 2; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int LRF() { return 1; }

  /**
   *  @brief Return the average fission flag
   */
  constexpr bool LFW() const { return false; }

  using UnresolvedBase::SPI;
  using UnresolvedBase::spin;
  using UnresolvedBase::AP;
  using UnresolvedBase::scatteringRadius;
  using UnresolvedBase::LSSF;
  using UnresolvedBase::selfShieldingOnly;

  using UnresolvedBase::type;
  using UnresolvedBase::representation;
  using UnresolvedBase::averageFissionWidthFlag;

  using UnresolvedBase::NLS;
  using UnresolvedBase::lValues;

  using UnresolvedBase::NC;
  using UnresolvedBase::print;
};
