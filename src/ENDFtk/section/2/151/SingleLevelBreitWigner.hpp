/**
 *  @class
 *  @brief Single level Breit-Wigner resonance parameters
 *
 *  The SingleLevelBreitWigner class is used to represent the SLBW
 *  parameters from MF2/MT151.
 *
 *  See ENDF102, section 2.2.1.1 for more information.
 */
class SingleLevelBreitWigner :
  protected BreitWignerReichMooreBase< BreitWignerLValue,
                                       SingleLevelBreitWigner > {

  friend BreitWignerReichMooreBase< BreitWignerLValue, SingleLevelBreitWigner >;

public:

  /* type alias */
  using LValue = BreitWignerLValue;

  /* constructor */
  #include "ENDFtk/section/2/151/SingleLevelBreitWigner/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int type() { return 1; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int representation() { return 1; }

  using BreitWignerReichMooreBase::LRU;
  using BreitWignerReichMooreBase::LRF;
  using BreitWignerReichMooreBase::LFW;
  using BreitWignerReichMooreBase::averageFissionWidthFlag;

  using BreitWignerReichMooreBase::SPI;
  using BreitWignerReichMooreBase::spin;
  using BreitWignerReichMooreBase::AP;
  using BreitWignerReichMooreBase::scatteringRadius;
  using BreitWignerReichMooreBase::NLS;
  using BreitWignerReichMooreBase::numberLValues;
  using BreitWignerReichMooreBase::lValues;

  using BreitWignerReichMooreBase::NC;
  using BreitWignerReichMooreBase::print;
};
