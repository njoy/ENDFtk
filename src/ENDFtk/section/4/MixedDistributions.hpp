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
class ENDFTK_PYTHON_EXPORT MixedDistributions {

  /* fields */
  LegendreDistributions legendre_;
  TabulatedDistributions tabulated_;

  /* workaround for the removal of range-v3 */

  // concat is not available in std20 or std23 so we generate the arrays
  // at construction time
  std::vector< long > interpolants_;
  std::vector< long > boundaries_;
  std::vector< double > energies_;
  std::vector< Variant > distributions_;
  #include "ENDFtk/section/4/MixedDistributions/src/generateArrays.hpp"

  /* auxiliary functions */
  #include "ENDFtk/section/4/MixedDistributions/src/verifyBoundary.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/4/MixedDistributions/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the isotropic angular distribution flag
   */
  static constexpr bool LI() { return false; }

  /**
   *  @brief Return the isotropic angular distribution flag
   */
  bool isotropicDistributions() const { return this->LI(); }

  /**
   *  @brief Return the angular distribution law
   */
  static constexpr int LTT() { return 3; }

  /**
   *  @brief Return the angular distribution law
   */
  int LAW() const { return this->LTT(); }

  /**
   *  @brief Return the Legendre distributions
   */
  const LegendreDistributions& legendre() const { return this->legendre_; }

  /**
   *  @brief Return the tabulated distributions
   */
  const TabulatedDistributions& tabulated() const { return this->tabulated_; }

  /**
   *  @brief Return the number of interpolation regions
   */
  long NR() const {

    return this->legendre().NR() + this->tabulated().NR();
  }

  /**
   *  @brief Return the number of interpolation regions
   */
  long numberInterpolationRegions() const { return this->NR(); }

  /**
   *  @brief Return the number of energy points for which angular distributions
   *         are available.
   */
  long NE() const {

    return this->legendre().NE() + this->tabulated().NE();
  }

  /**
   *  @brief Return the number of energy points for which angular distributions
   *         are available.
   */
  long numberIncidentEnergies() const { return this->NE(); }

  /**
   *  @brief Return the boundaries of the interpolation ranges
   *
   *         The intersection point is considered as a jump in the incident
   *         energy.
   */
  auto NBT() const {

    using namespace njoy::tools;
    return std20::views::all( this->boundaries_ );
  }

  /**
   *  @brief Return the boundaries of the interpolation ranges
   *
   *         The intersection point is considered as a jump in the incident
   *         energy.
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return the interpolants of the interpolation ranges
   */
  auto INT() const {

    using namespace njoy::tools;
    return std20::views::all( this->interpolants_ );
  }

  /**
   *  @brief Return the interpolants of the interpolation ranges
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return the incident energy values
   */
  auto incidentEnergies() const {

    using namespace njoy::tools;
    return std20::views::all( this->energies_ );
  }

  /**
   *  @brief Return the angular distributions (one for each incident energy)
   *
   *  This function returns the underlying angular distributions as a variant
   *  of reference wrappers. See the MixedDistributions unit test for more
   *  information on how to use this.
   */
  auto angularDistributions() const {

    using namespace njoy::tools;
    return std20::views::all( this->distributions_ );
  }

  /**
   *  @brief Return the number of lines for this ENDF component
   */
  long NC() const { return this->legendre_.NC() +
  	                       this->tabulated_.NC(); }

  #include "ENDFtk/section/4/MixedDistributions/src/print.hpp"
};
