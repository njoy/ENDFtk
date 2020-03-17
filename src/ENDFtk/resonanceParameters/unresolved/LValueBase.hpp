/**
 *  @class
 *  @brief Base class for an l value in the unresolved resonances (used for
 *         energy dependent fission widths and all energy dependent widths).
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
template < typename JValue > class LValueBase {

  /* fields */
  double awri_;
  int l_;
  std::vector< JValue > jvalues_;

  /* auxiliary functions */
  #include "ENDFtk/resonanceParameters/unresolved/LValueBase/src/readJValues.hpp"
  #include "ENDFtk/resonanceParameters/unresolved/LValueBase/src/verifySize.hpp"

public:

  /* constructor */
  #include "ENDFtk/resonanceParameters/unresolved/LValueBase/src/ctor.hpp"

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

  #include "ENDFtk/resonanceParameters/unresolved/LValueBase/src/NC.hpp"
  #include "ENDFtk/resonanceParameters/unresolved/LValueBase/src/print.hpp"
};
