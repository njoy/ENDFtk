class EnergyDependentFissionWidths;
template <>
struct LJValueType< EnergyDependentFissionWidths > {

  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/JValue.hpp"
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/LValue.hpp"

  using jtype = JValue;
  using ltype = LValue;
};

/**
 *  @class
 *  @brief Single level Breit-Wigner unresolved resonance parameters with
 *         energy dependent fission widths and energy independent widths for the
 *         other reactions.
 *
 *  The EnergyDependentFissionWidths class is used to represent the
 *  SLBW unresolved parameters from MF2/MT151 for LRU=2 LRF=1 LFW=1.
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
class EnergyDependentFissionWidths :
    public UnresolvedBaseWithoutSpin< EnergyDependentFissionWidths > {

public:

  using JValue = LJValueType< EnergyDependentFissionWidths >::jtype;
  using LValue = LJValueType< EnergyDependentFissionWidths >::ltype;

private:

  /* fields */
  ListRecord energies_;

  /* auxiliary functions */
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/src/verifySize.hpp"

public:

  /* constructors */
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/src/ctor.hpp"

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
  using UnresolvedBaseWithoutSpin::lValues;

  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/src/NC.hpp"
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/src/print.hpp"
};
