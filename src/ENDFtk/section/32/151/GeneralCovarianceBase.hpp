/**
 *  @class
 *  @brief Base class for general covariance representations (LCOMP = 1)
 *
 *  The GeneralCovarianceBase class is used to represent the resonance and
 *  covariance representations (LRU=1 and LRF=1, 2, 3, 4 and 7) for LCOMP=0
 *  from MF32/MT151.
 *
 *  See ENDF102, section 32.2.2 for more information.
 */
template < typename ShortRangeCovarianceBlock,
           typename RadiusUncertainty,
           typename Derived >
class GeneralCovarianceBase {

  /* fields */
  double spi_;
  double ap_;
  std::optional< RadiusUncertainty > dap_;

  std::vector< ShortRangeCovarianceBlock > short_;
  std::vector< LongRangeCovarianceBlock > long_;

  /* auxiliary functions */
  #include "ENDFtk/section/32/151/GeneralCovarianceBase/src/readSequence.hpp"
  #include "ENDFtk/section/32/151/GeneralCovarianceBase/src/verifySize.hpp"

protected:

  /* constructor */
  #include "ENDFtk/section/32/151/GeneralCovarianceBase/src/ctor.hpp"

public:

  /* get methods */

  /**
   *  @brief Return the covariance representation type
   */
  static constexpr int LCOMP() { return 1; }

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
  const std::optional< RadiusUncertainty >& DAP() const { return this->dap_; }

  /**
   *  @brief Return the scattering radius uncertainty
   */
  const std::optional< RadiusUncertainty >& scatteringRadiusUncertainty() const {

    return this->DAP();
  }

  /**
   *  @brief Return the number of short range covariance blocks
   */
  int NSRS() const { return this->short_.size(); }

  /**
   *  @brief Return the number of short range covariance blocks
   */
  int numberShortRangeBlocks() const { return this->NLS(); }

  /**
   *  @brief Return the number of long range covariance blocks
   */
  int NLRS() const { return this->long_.size(); }

  /**
   *  @brief Return the number of short range covariance blocks
   */
  int numberLongRangeBlocks() const { return this->NLS(); }

  /**
   *  @brief Return the scattering radius uncertainty flag
   */
  bool ISR() const { return bool( this->dap_ ); }

  /**
   *  @brief Return the angular distribution flag
   */
  bool scatteringRadiusUncertaintyFlag() const { return this->ISR(); }

  /**
   *  @brief Return the short range resonance covariance blocks
   */
  auto shortRangeBlocks() const {

    return ranges::cpp20::views::all( this->short_ );
  }

  /**
   *  @brief Return the long range resonance covariance blocks
   */
  auto longRangeBlocks() const {

    return ranges::cpp20::views::all( this->long_ );
  }

  #include "ENDFtk/section/32/151/GeneralCovarianceBase/src/NC.hpp"
  #include "ENDFtk/section/32/151/GeneralCovarianceBase/src/print.hpp"
};
