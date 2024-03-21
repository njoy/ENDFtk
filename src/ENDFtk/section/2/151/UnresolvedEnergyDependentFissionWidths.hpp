class UnresolvedEnergyDependentFissionWidths;
template < typename GCC >
struct LJValueType< UnresolvedEnergyDependentFissionWidths, GCC > {

  #include "ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/JValue.hpp"
  #include "ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/LValue.hpp"

  using JType = JValue;
  using LType = LValue;
};

/**
 *  @class
 *  @brief Single level Breit-Wigner unresolved resonance parameters with
 *         energy dependent fission widths and energy independent widths for the
 *         other reactions.
 *
 *  The UnresolvedEnergyDependentFissionWidths class is used to represent the
 *  SLBW unresolved parameters from MF2/MT151 for LRU=2 LRF=1 LFW=1.
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT UnresolvedEnergyDependentFissionWidths :
    public UnresolvedBaseWithoutSpin< UnresolvedEnergyDependentFissionWidths > {

public:

  using JValue = LJValueType< UnresolvedEnergyDependentFissionWidths >::JType;
  using LValue = LJValueType< UnresolvedEnergyDependentFissionWidths >::LType;

private:

  /* fields */
  ListRecord energies_;

  /* auxiliary functions */
  #include "ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/src/verifySize.hpp"

public:

  /* constructors */
  #include "ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/src/ctor.hpp"

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
  constexpr bool LFW() const { return true; }

  /**
   *  @brief Return the target spin
   */
  double SPI() const { return this->energies_.C1(); }

  /**
   *  @brief Return the scattering radius
   */
  double AP() const { return this->energies_.C2(); }

  /**
   *  @brief Return the self-shielding only flag
   */
  bool LSSF() const { return this->energies_.L1(); }

  /**
   *  @brief Return the energy values
   */
  int NE() const { return this->energies_.NPL(); }

  /**
   *  @brief Return the energy values for which fission widths are given
   */
  auto ES() const { return this->energies_.list(); }

  /**
   *  @brief Return the energy values for which fission widths are given
   */
  auto energies() const { return this->ES(); }

  using UnresolvedBaseWithoutSpin::spin;
  using UnresolvedBaseWithoutSpin::scatteringRadius;
  using UnresolvedBaseWithoutSpin::selfShieldingOnly;

  using UnresolvedBaseWithoutSpin::type;
  using UnresolvedBaseWithoutSpin::representation;
  using UnresolvedBaseWithoutSpin::averageFissionWidthFlag;

  using UnresolvedBaseWithoutSpin::NLS;
  using UnresolvedBaseWithoutSpin::numberLValues;
  using UnresolvedBaseWithoutSpin::lValues;

  #include "ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/src/NC.hpp"
  #include "ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/src/print.hpp"
};
