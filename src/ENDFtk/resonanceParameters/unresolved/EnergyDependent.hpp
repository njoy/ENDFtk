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
class EnergyDependent {

public:

  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependent/JValue.hpp"
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependent/LValue.hpp"

//private:

  /* fields */
//  ListRecord energies_;
//  std::vector< LValue > lvalues_;

  /* auxiliary functions */
//  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/src/readLValues.hpp"
//  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/src/verifySize.hpp"

public:

  /* constructors */
//  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependent/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
//  static constexpr int LRU() { return 2; }

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
//  static constexpr int type() { return EnergyDependentFissionWidths::LRU(); }

  /**
   *  @brief Return the resonance representation
   */
//  static constexpr int LRF() { return 2; }

  /**
   *  @brief Return the resonance representation
   */
/*  static constexpr int representation() {

    return EnergyDependentFissionWidths::LRF();
  }
*/
  /**
   *  @brief Return the average fission flag
   */
//  constexpr bool LFW() const { return true; }

  /**
   *  @brief Return the average fission flag
   */
/*  constexpr int averageFissionWidthFlag() const {

    return EnergyDependentFissionWidths::LFW();
  }
*/
  /**
   *  @brief Return the data for every l value
   */
//  auto lValues() const { return ranges::view::all( this->lvalues_ ); }
};
