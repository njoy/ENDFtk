/**
 *  @class
 *  @brief Base class for limited Breit-Wigner resonance and covariance
 *         representations (LCOMP = 0)
 *
 *  The LimitedCovarianceBase class is used to represent the SLBW and MLBW
 *  resonance and covariance representations (LRU=1 and LRF=1, 2) for LCOMP=0
 *  from MF32/MT151.
 *
 *  See ENDF102, section 32.2.1 for more information.
 */
template < typename Derived > class LimitedCovarianceBase {

  /* fields */
  double spi_;
  double ap_;
  std::optional< double > dap_;

  std::vector< LimitedBreitWignerLValue > lvalues_;

  /* auxiliary functions */
  #include "ENDFtk/section/32/151/LimitedCovarianceBase/src/verifySize.hpp"

protected:

  /* constructor */
  #include "ENDFtk/section/32/151/LimitedCovarianceBase/src/ctor.hpp"

public:

  /* get methods */

  /**
   *  @brief Return the covariance representation type
   */
  static constexpr int LCOMP() { return 0; }

  /**
   *  @brief Return the covariance representation type
   */
  constexpr int covarianceRepresentation() const { return this->LCOMP(); }

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

    return this->LFW();
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
   *  @brief Return the scattering radius uncertainty
   */
  const std::optional< double >& DAP() const { return this->dap_; }

  /**
   *  @brief Return the scattering radius uncertainty
   */
  const std::optional< double >& scatteringRadiusUncertainty() const {

    return this->DAP();
  }

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
   *  @brief Return the scattering radius uncertainty flag
   */
  bool ISR() const { return bool( this->dap_ ); }

  /**
   *  @brief Return the angular distribution flag
   */
  bool scatteringRadiusUncertaintyFlag() const { return this->ISR(); }

  /**
   *  @brief Return the l values and its resonance parameters
   */
  auto lValues() const {

    return ranges::cpp20::views::all( this->lvalues_ );
  }

  #include "ENDFtk/section/32/151/LimitedCovarianceBase/src/NC.hpp"
  #include "ENDFtk/section/32/151/LimitedCovarianceBase/src/print.hpp"
};
