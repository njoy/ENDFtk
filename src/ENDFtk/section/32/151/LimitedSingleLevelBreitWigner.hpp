/**
 *  @class
 *  @brief Limited single level Breit-Wigner resonance parameter covariances
 *
 *  See ENDF102, section 32.2.1
 */
class LimitedSingleLevelBreitWigner :
  protected LimitedCovarianceBase< LimitedSingleLevelBreitWigner > {

  friend LimitedCovarianceBase< LimitedSingleLevelBreitWigner >;

public:

  /* type alias */
  using LValue = LimitedBreitWignerLValue;

  /* constructor */
  #include "ENDFtk/section/32/151/LimitedSingleLevelBreitWigner/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int type() { return 1; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int representation() { return 1; }

  using LimitedCovarianceBase::LRU;
  using LimitedCovarianceBase::LRF;
  using LimitedCovarianceBase::LFW;
  using LimitedCovarianceBase::averageFissionWidthFlag;
  using LimitedCovarianceBase::LCOMP;
  using LimitedCovarianceBase::covarianceRepresentation;

  using LimitedCovarianceBase::SPI;
  using LimitedCovarianceBase::spin;
  using LimitedCovarianceBase::AP;
  using LimitedCovarianceBase::scatteringRadius;
  using LimitedCovarianceBase::DAP;
  using LimitedCovarianceBase::scatteringRadiusUncertainty;
  using LimitedCovarianceBase::NLS;
  using LimitedCovarianceBase::numberLValues;
  using LimitedCovarianceBase::ISR;
  using LimitedCovarianceBase::scatteringRadiusUncertaintyFlag;
  using LimitedCovarianceBase::lValues;

  using LimitedCovarianceBase::NC;
  using LimitedCovarianceBase::print;
};
