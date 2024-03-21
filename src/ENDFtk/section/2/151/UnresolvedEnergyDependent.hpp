class UnresolvedEnergyDependent;
template < typename GCC >
struct LJValueType< UnresolvedEnergyDependent, GCC > {

  #include "ENDFtk/section/2/151/UnresolvedEnergyDependent/JValue.hpp"
  #include "ENDFtk/section/2/151/UnresolvedEnergyDependent/LValue.hpp"

  using JType = JValue;
  using LType = LValue;
};

/**
 *  @class
 *  @brief Single level Breit-Wigner unresolved resonance parameters with
 *         energy dependent resonance widths.
 *
 *  The UnresolvedEnergyDependent class is used to represent the
 *  SLBW unresolved parameters from MF2/MT151 for LRU=2 LRF=2 (no LFW
 *  dependence).
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT UnresolvedEnergyDependent :
  public UnresolvedBase< UnresolvedEnergyDependent > {

public:

  using JValue = LJValueType< UnresolvedEnergyDependent >::JType;
  using LValue = LJValueType< UnresolvedEnergyDependent >::LType;

  /* constructor */
  #include "ENDFtk/section/2/151/UnresolvedEnergyDependent/src/ctor.hpp"

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
  using UnresolvedBase::numberLValues;
  using UnresolvedBase::lValues;

  using UnresolvedBase::NC;
  using UnresolvedBase::print;
};
