/**
 *  @class
 *  @brief Base class for an l value in the unresolved resonances (used for
 *         energy dependent fission widths and all energy dependent widths).
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
template < typename JValue > class UnresolvedLValueBase {

  /* fields */
  double awri_;
  int l_;
  std::vector< JValue > jvalues_;

  /* auxiliary functions */
  #include "ENDFtk/section/2/151/UnresolvedLValueBase/src/verifySize.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/2/151/UnresolvedLValueBase/src/ctor.hpp"

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
  auto jValues() const { 

    return ranges::cpp20::views::all( this->jvalues_ );
  }

  /**
   *  @brief Return the number of fission width values
   */
  unsigned int NE() const { return this->jvalues_.front().NE(); }

  #include "ENDFtk/section/2/151/UnresolvedLValueBase/src/NC.hpp"
  #include "ENDFtk/section/2/151/UnresolvedLValueBase/src/print.hpp"
};
