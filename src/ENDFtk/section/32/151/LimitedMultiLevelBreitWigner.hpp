/**
 *  @class
 *  @brief Limited single level Breit-Wigner resonance parameter covariances
 *
 *  See ENDF102, section 32.2.1
 */
class LimitedMultiLevelBreitWigner :
  protected BreitWignerBase< BreitWignerLValue, LimitedMultiLevelBreitWigner > {

  friend BreitWignerBase< BreitWignerLValue, LimitedMultiLevelBreitWigner >;

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

  using BreitWignerBase::LCOMP;
  using BreitWignerBase::LRU;
  using BreitWignerBase::LRF;
  using BreitWignerBase::LFW;
  using BreitWignerBase::averageFissionWidthFlag;

  using BreitWignerBase::SPI;
  using BreitWignerBase::spin;
  using BreitWignerBase::AP;
  using BreitWignerBase::scatteringRadius;
  using BreitWignerBase::DAP;
  using BreitWignerBase::scatteringRadiusUncertainty;
  using BreitWignerBase::NLS;
  using BreitWignerBase::numberLValues;
  using BreitWignerBase::ISR;
  using BreitWignerBase::scatteringRadiusUncertaintyFlag;
  using BreitWignerBase::lValues;

  using BreitWignerBase::NC;
  using BreitWignerBase::print;
};
