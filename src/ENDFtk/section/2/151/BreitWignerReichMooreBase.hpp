/**
 *  @class
 *  @brief Base class for Breit-Wigner and Reich-Moore resonance representations
 *
 *  The BreitWignerReichMooreBase class is used to represent the SLBW, MLBW and
 *  RM resonance representations (LRU=1 and LRF=1, 2 or 3) from MF2/MT151.
 *
 *  See ENDF102, section 2.2.1.1 and 2.2.1.2 for more information.
 */
template < typename LValue, typename Derived >
class BreitWignerReichMooreBase {

  /* fields */
  double spi_;
  double ap_;
  bool lad_;
  int nlsc_;

  std::vector< LValue > lvalues_;

  /* auxiliary functions */
  #include "ENDFtk/section/2/151/BreitWignerReichMooreBase/src/verifySize.hpp"

protected:

  /* constructor */
  #include "ENDFtk/section/2/151/BreitWignerReichMooreBase/src/ctor.hpp"

public:

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  constexpr int LRU() const {

    return static_cast< const Derived* >( this )->type();
  }

  /**
   *  @brief Return the resonance representation
   */
  constexpr int LRF() const {

    return static_cast< const Derived* >( this )->representation();
  }

  /**
   *  @brief Return the average fission flag
   */
  constexpr bool LFW() const { return false; }

  /**
  *  @brief Return the average fission flag
  */
  constexpr int averageFissionWidthFlag() const {

    return BreitWignerReichMooreBase::LFW();
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
   *  @brief Return the angular distribution flag
   */
  bool LAD() const { return this->lad_; }

  /**
   *  @brief Return the angular distribution flag
   */
  bool angularDistributionsFlag() const { return this->LAD(); }

  /**
   *  @brief Return the number of l values for which resonance parameters are
   *         given
   */
  int NLS() const { return this->lvalues_.size(); }

  /**
   *  @brief Return the number of l values for which resonance parameters are
   *         given
   */
  int numberLValues() const { return this->NLS(); }

  /**
   *  @brief Return the number of l values required for convergence
   */
  int NLSC() const { return this->nlsc_; }

  /**
   *  @brief Return the number of l values required for convergence
   */
  int numberLValuesForConvergence() const { return this->NLSC(); }

  /**
   *  @brief Return the l values and its resonance parameters
   */
  auto lValues() const {

    return ranges::cpp20::views::all( this->lvalues_ );
  }

  #include "ENDFtk/section/2/151/BreitWignerReichMooreBase/src/NC.hpp"
  #include "ENDFtk/section/2/151/BreitWignerReichMooreBase/src/print.hpp"
};
