/**
 *  @class
 *  @brief The angular distributions are mixed (Legendre coefficients and
 *         tabulated distributions)
 *
 *  The MixedDistributions class is used to represent the case in which
 *  the angular distributions are are given as a region of Legendre
 *  distributions followed by a region of tabulated ditributions.
 *
 *  See ENDF102, section 4.2.3 for more information.
 */
class MixedDistributions {

  /* fields */
  LegendreDistributions legendre_;
  TabulatedDistributions tabulated_;

  /* auxiliary functions */
  #include "ENDFtk/section/4/MixedDistributions/src/verifyBoundary.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/4/MixedDistributions/src/ctor.hpp"

  /* get methods */

  /** 
   *  @brief Return the angular distribution law
   */
  static constexpr int LTT() { return 3; }

  /** 
   *  @brief Return the angular distribution law
   */
  static constexpr int LAW() { return MixedDistributions::LTT(); }

  /** 
   *  @brief Return the Legendre distributions
   */
  const auto& legendre() const { return this->legendre_; }

  /** 
   *  @brief Return the tabulated distributions
   */
  const auto& tabulated() const { return this->tabulated_; }

  /** 
   *  @brief Return the number of lines for this ENDF component
   */
  long NC() const { return this->legendre_.NC() +
  	                       this->tabulated_.NC(); }

  #include "ENDFtk/section/4/MixedDistributions/src/print.hpp"
};
