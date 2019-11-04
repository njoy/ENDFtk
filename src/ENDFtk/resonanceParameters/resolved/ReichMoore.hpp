/**
 *  @class
 *  @brief Reich-Moore resonance parameters
 *
 *  The SingleLevelBreitWigner class is used to represent the Reich-Moore
 *  parameters from MF2/MT151.
 *
 *  See ENDF102, section 2.2.1.2 for more information.
 */
class ReichMoore :
  protected BreitWignerReichMooreBase< ReichMooreLValue, ReichMoore > {

  friend BreitWignerReichMooreBase< ReichMooreLValue, ReichMoore >;

  /* auxiliary functions */
  #include "ENDFtk/resonanceParameters/resolved/ReichMoore/src/verifyNLSC.hpp"

public:

  /* constructor */
  #include "ENDFtk/resonanceParameters/resolved/ReichMoore/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int type() { return 1; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int representation() { return 3; }

  using BreitWignerReichMooreBase::LRU;
  using BreitWignerReichMooreBase::LRF;
  using BreitWignerReichMooreBase::LFW;
  using BreitWignerReichMooreBase::averageFissionWidthFlag;

  using BreitWignerReichMooreBase::SPI;
  using BreitWignerReichMooreBase::spin;
  using BreitWignerReichMooreBase::AP;
  using BreitWignerReichMooreBase::scatteringRadius;
  using BreitWignerReichMooreBase::LAD;
  using BreitWignerReichMooreBase::angularDistributionsFlag;
  using BreitWignerReichMooreBase::NLS;
  using BreitWignerReichMooreBase::numberLValues;
  using BreitWignerReichMooreBase::NLSC;
  using BreitWignerReichMooreBase::numberLValuesForConvergence;
  using BreitWignerReichMooreBase::lValues;

  using BreitWignerReichMooreBase::NC;
  using BreitWignerReichMooreBase::print;
};
