/**
 *  @class
 *  @brief Base class for compact covariance representations (LCOMP = 2)
 *
 *  The CompactCovarianceBase class is used to represent the resonance and
 *  covariance representations (LRU=1 and LRF = 1, 2, 3 and 7) for LCOMP = 2
 *  from MF32/MT151.
 *
 *  See ENDF102, section 32.2.3 for more information.
 */
template < typename ResonanceParameterUncertainties,
           typename RadiusUncertainty,
           typename Derived >
class CompactCovarianceBase {

  /* fields */
  double spi_;
  double ap_;
  long l1_;
  long n1_;
  std::optional< RadiusUncertainty > dap_;

  ResonanceParameterUncertainties uncertainties_;
  CompactCorrelationMatrix matrix_;

  /* auxiliary functions */

protected:

  /* constructor */
  #include "ENDFtk/section/32/151/CompactCovarianceBase/src/ctor.hpp"

public:

  /* get methods */

  /**
   *  @brief Return the covariance representation type
   */
  static constexpr int LCOMP() { return 2; }

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
  static constexpr bool LFW() { return false; }

  /**
  *  @brief Return the average fission flag
  */
  constexpr bool averageFissionWidthFlag() const {

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
   *  @brief Return the value of L1
   */
  long L1() const { return this->l1_; }

  /**
   *  @brief Return the value of N1
   */
  long N1() const { return this->n1_; }

  /**
   *  @brief Return the scattering radius uncertainty
   */
  const std::optional< RadiusUncertainty >& DAP() const { return this->dap_; }

  /**
   *  @brief Return the scattering radius uncertainty
   */
  const std::optional< RadiusUncertainty >& scatteringRadiusUncertainty() const {

    return this->DAP();
  }

  /**
   *  @brief Return the scattering radius uncertainty flag
   */
  bool ISR() const { return bool( this->dap_ ); }

  /**
   *  @brief Return the angular distribution flag
   */
  bool scatteringRadiusUncertaintyFlag() const { return this->ISR(); }

  /**
   *  @brief Return the resonance parameter uncertainties
   */
  const ResonanceParameterUncertainties& uncertainties() const {

    return this->uncertainties_;
  }

  /**
   *  @brief Return the correlation matrix
   */
  const CompactCorrelationMatrix& correlationMatrix() const {

    return this->matrix_;
  }

  #include "ENDFtk/section/32/151/CompactCovarianceBase/src/NC.hpp"
  #include "ENDFtk/section/32/151/CompactCovarianceBase/src/print.hpp"
};
