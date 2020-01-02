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
class EnergyDependentFissionWidths {

public:

  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/JValue.hpp"
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/LValue.hpp"

private:

  /* fields */
  ListRecord energies_;
  std::vector< LValue > lvalues_;

  /* auxiliary functions */
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/src/readLValues.hpp"
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
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int type() { return EnergyDependentFissionWidths::LRU(); }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int LRF() { return 1; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int representation() {

    return EnergyDependentFissionWidths::LRF();
  }

  /**
   *  @brief Return the average fission flag
   */
  constexpr bool LFW() const { return true; }

  /**
   *  @brief Return the average fission flag
   */
  constexpr int averageFissionWidthFlag() const {

    return EnergyDependentFissionWidths::LFW();
  }

  /**
   *  @brief Return the target spin
   */
  double SPI() const { return this->energies_.C1(); }

  /**
   *  @brief Return the target spin
   */
  double spin() const { return this->SPI(); }

  /**
   *  @brief Return the scattering radius
   */
  double AP() const { return this->energies_.C2(); }

  /**
   *  @brief Return the scattering radius
   */
  double scatteringRadius() const { return this->AP(); }

  /**
   *  @brief Return the self-shielding only flag
   */
  bool LSSF() const { return this->energies_.L1(); }

  /**
   *  @brief Return the self-shielding only flag
   */
  bool selfShieldingOnly() const { return this->LSSF(); }

  /**
   *  @brief Return the energy values
   */
  int NE() const { return this->energies_.NPL(); }

  /**
   *  @brief Return the number of l values
   */
  int NLS() const { return this->lvalues_.size(); }

  /**
   *  @brief Return the energy values for which fission widths are given
   */
  auto ES() const { return this->energies_.list(); }

  /**
   *  @brief Return the energy values for which fission widths are given
   */
  auto energies() const { return this->ES(); }

  /**
   *  @brief Return the data for every l value
   */
  auto lValues() const { return ranges::view::all( this->lvalues_ ); }

  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/src/NC.hpp"
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/src/print.hpp"
};
