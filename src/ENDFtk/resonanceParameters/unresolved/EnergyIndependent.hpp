/**
 *  @class
 *  @brief Single level Breit-Wigner unresolved resonance parameters with
 *         energy independent widths and no fission given
 *
 *  The EnergyIndependentSingleLevelBreitWigner class is used to represent the
 *  SLBW unresolved parameters from MF2/MT151 for LRU=2 LRF=1 LFW=0.
 *
 *  See ENDF102, section 2.2.1.1 for more information.
 */
class EnergyIndependent {

public:

  #include "ENDFtk/resonanceParameters/unresolved/EnergyIndependent/JValue.hpp"
  #include "ENDFtk/resonanceParameters/unresolved/EnergyIndependent/LValue.hpp"

private:

  /* fields */
  double spi_;
  double ap_;
  bool lssf_;

  std::vector< LValues > lvalues_;

public:

  /* constructor */
  #include "ENDFtk/resonanceParameters/unresolved/EnergyIndependent/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int LRU() { return 2; }

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int type() { return RMatrixLimited::LRU(); }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int LRF() { return 1; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int representation() { return RMatrixLimited::LRF(); }

  /**
   *  @brief Return the average fission flag
   */
  constexpr bool LFW() const { return false; }

  /**
   *  @brief Return the average fission flag
   */
  constexpr int averageFissionWidthFlag() const {

    return RMatrixLimited::LFW();
  }

  /**
   *  @brief Return the target spin
   */
  double SPI() const { return this->spi_; }

  /**
   *  @brief Return the target spin
   */
  double spin() const { return this->SPI(); }

  /**
   *  @brief Return the scattering radius
   */
  double AP() const { return this->ap_; }

  /**
   *  @brief Return the scattering radius
   */
  double scatteringRadius() const { return this->AP(); }

  /**
   *  @brief Return the self-shielding only flag
   */
  bool LSSF() const { return this->lssf_; }

  /**
   *  @brief Return the self-shielding only flag
   */
  bool selfShieldingOnly() const { return this->LSSF(); }

  /**
   *  @brief Return the number of l values for which data is available
   */
  int NLS() const { return this->lvalues_.size(); }

  /**
   *  @brief Return the l value data
   */
  auto lValues() const { return ranges::view::all( this->lvalues_ ); }

  #include "ENDFtk/resonanceParameters/unresolved/EnergyIndependent/src/NC.hpp"
  #include "ENDFtk/resonanceParameters/unresolved/EnergyIndependent/src/print.hpp"
};
