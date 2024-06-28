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

//  /**
//   *  @brief Return the boundaries of the interpolation ranges
//   *
//   *         The intersection point is considered as a jump in the incident
//   *         energy.
//   */
//  auto NBT() const {
//
//    auto offset = this->legendre().NBT().back();
//    return ranges::views::concat(
//             this->legendre().NBT(),
//             this->tabulated().NBT()
//               | ranges::cpp20::views::transform(
//                     [=] ( auto index )
//                         { return index + offset; } ) );
//  }
//
//  /**
//   *  @brief Return the boundaries of the interpolation ranges
//   *
//   *         The intersection point is considered as a jump in the incident
//   *         energy.
//   */
//  auto boundaries() const { return this->NBT(); }
//
//  /**
//   *  @brief Return the interpolants of the interpolation ranges
//   */
//  auto INT() const {
//
//    return ranges::views::concat( this->legendre().INT(),
//                                  this->tabulated().INT() );
//  }
//
//  /**
//   *  @brief Return the interpolants of the interpolation ranges
//   */
//  auto interpolants() const { return this->INT(); }
//
//  /**
//   *  @brief Return the incident energy values
//   */
//  auto incidentEnergies() const {
//
//    return ranges::views::concat( this->legendre().incidentEnergies(),
//                                  this->tabulated().incidentEnergies() );
//  }
//
//  #include "ENDFtk/section/4/MixedDistributions/src/angularDistributions.hpp"

  /**
   *  @brief Return the number of lines for this ENDF component
   */
  long NC() const { return this->legendre_.NC() +
  	                       this->tabulated_.NC(); }

  #include "ENDFtk/section/4/MixedDistributions/src/print.hpp"
};
