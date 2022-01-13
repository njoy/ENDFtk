/**
 *  @class
 *  @brief Limited single level Breit-Wigner resonance parameter covariances
 *
 *  See ENDF102, section 32.2.1
 */
class LimitedMultiLevelBreitWigner :
  protected LimitedBreitWignerBase< BreitWignerLValue, LimitedMultiLevelBreitWigner > {

  friend LimitedBreitWignerBase< BreitWignerLValue, LimitedMultiLevelBreitWigner >;

public:

  /* type alias */
  using LValue = BreitWignerLValue;

  /* constructor */
  #include "ENDFtk/section/32/151/LimitedMultiLevelBreitWigner/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int type() { return 1; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int representation() { return 2; }

  /**
   *  @brief Return the covariance representation type
   */
  static constexpr int covarianceRepresentation() { return 0; }

  using LimitedBreitWignerBase::LCOMP;
  using LimitedBreitWignerBase::LRU;
  using LimitedBreitWignerBase::LRF;
  using LimitedBreitWignerBase::LFW;
  using LimitedBreitWignerBase::averageFissionWidthFlag;

  using LimitedBreitWignerBase::SPI;
  using LimitedBreitWignerBase::spin;
  using LimitedBreitWignerBase::AP;
  using LimitedBreitWignerBase::scatteringRadius;
  using LimitedBreitWignerBase::DAP;
  using LimitedBreitWignerBase::scatteringRadiusUncertainty;
  using LimitedBreitWignerBase::NLS;
  using LimitedBreitWignerBase::numberLValues;
  using LimitedBreitWignerBase::ISR;
  using LimitedBreitWignerBase::scatteringRadiusUncertaintyFlag;
  using LimitedBreitWignerBase::lValues;

  using LimitedBreitWignerBase::NC;
  using LimitedBreitWignerBase::print;
};
