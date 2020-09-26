class EnergyDependent;
template <>
struct LJValueType< EnergyDependent > {

  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependent/JValue.hpp"
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependent/LValue.hpp"

  using JType = JValue;
  using LType = LValue;
};

/**
 *  @class
 *  @brief Single level Breit-Wigner unresolved resonance parameters with
 *         energy dependent resonance widths.
 *
 *  The EnergyDependent class is used to represent the
 *  SLBW unresolved parameters from MF2/MT151 for LRU=2 LRF=2 (no LFW
 *  dependence).
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
class EnergyDependent : public UnresolvedBase< EnergyDependent > {

public:

  using JValue = LJValueType< EnergyDependent >::JType;
  using LValue = LJValueType< EnergyDependent >::LType;

  /* constructor */
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependent/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int LRU() { return 2; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int LRF() { return 2; }

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
