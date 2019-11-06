/**
 *  @class
 *  @brief The unresolved resonance parameters for a given l value in the SLBW
 *         representation for energy dependent fission widths (all other
 *         widths are energy independent).
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
class LValue {

  /* fields */
  double awri_;
  int l_;
  std::vector< JValue > jvalues_;

  /* auxiliary functions */
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/LValue/src/readJValues.hpp"
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/LValue/src/verifySize.hpp"

public:

  /* constructor */
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/LValue/src/ctor.hpp"

  /**
   *  @brief Return the atomic weight ratio of the current isotope to the
   *         neutron mass
   */
  double AWRI() const { return this->awri_; }

  /**
   *  @brief Return the atomic weight ratio of the current isotope to the
   *         neutron mass
   */
  double atomicWeightRatio() const { return this->AWRI(); }

  /**
   *  @brief Return the value of the orbital momentum l
   */
  int L() const { return this->l_; }

  /**
   *  @brief Return the value of the orbital momentum l
   */
  int orbitalMomentum() const { return this->L(); }

  /**
   *  @brief Return the number of J values for this l value
   */
  int NJS() const { return this->jvalues_.size(); }

  /**
   *  @brief Return the number of J values for this l value
   */
  int numberSpinValues() const { return this->NJS(); }

  /**
   *  @brief Return the data for each of the J values
   */
  auto jValues() const { return ranges::view::all( this->jvalues_ ); }

  /**
   *  @brief Return the number of fission width values
   */
  unsigned int NE() const { return this->jvalues_.front().NE(); }

  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/LValue/src/NC.hpp"
  #include "ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/LValue/src/print.hpp"
};
