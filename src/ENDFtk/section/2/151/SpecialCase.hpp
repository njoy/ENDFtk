/**
 *  @class
 *  @brief Special case: no parameters are given (LRU=0, LRF=0)
 *
 *  The SpecialCase class is used to represent the special case where only
 *  the spin and scattering radius are given in MF2/MT151.
 *
 *  See ENDF102, section 2.1 for more information.
 */
class SpecialCase {

  /* fields */
  double spi_;
  double ap_;

public:

  /* constructor */
  #include "ENDFtk/section/2/151/SpecialCase/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int LRU() { return 0; }

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int type() { return SpecialCase::LRU(); }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int LRF() { return 0; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int representation() { return SpecialCase::LRF(); }

  /**
   *  @brief Return the average fission flag
   */
  static constexpr bool LFW() { return false; }

  /**
   *  @brief Return the average fission flag
   */
  static constexpr bool averageFissionWidthFlag() { return SpecialCase::LFW(); }

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
   *  @brief Return the number of lines in this MF2 MT151 component
   */
  long NC() const { return 1; }

  #include "ENDFtk/section/2/151/SpecialCase/src/print.hpp"
};
