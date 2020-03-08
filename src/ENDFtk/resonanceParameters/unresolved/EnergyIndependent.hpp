class EnergyIndependent;
template <>
struct LJValueType< EnergyIndependent > {

  #include "ENDFtk/resonanceParameters/unresolved/EnergyIndependent/JValue.hpp"
  #include "ENDFtk/resonanceParameters/unresolved/EnergyIndependent/LValue.hpp"

  template < typename Range > using jtype = JValue< Range >;
  using ltype = LValue;
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
class EnergyIndependent : public UnresolvedBase< EnergyIndependent > {

public:

  template < typename Range >
  using JValue = LJValueType< EnergyIndependent >::jtype< Range >;
  using LValue = LJValueType< EnergyIndependent >::ltype;

  /* constructor */
  #include "ENDFtk/resonanceParameters/unresolved/EnergyIndependent/src/ctor.hpp"

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
