/**
 *  @class
 *  @brief Multilevel Breit-Wigner resonance parameters
 *
 *  The MultiLevelBreitWigner class is used to represent the MLBW
 *  parameters from MF2/MT151.
 *
 *  See ENDF102, section 2.2.1.1 for more information.
 */
class MultiLevelBreitWigner :
  protected BreitWignerReichMooreBase< BreitWignerLValue,
                                       MultiLevelBreitWigner > {

  friend BreitWignerReichMooreBase< BreitWignerLValue, MultiLevelBreitWigner >;

public:

  /* constructor */
  #include "ENDFtk/resonanceParameters/resolved/MultiLevelBreitWigner/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int type() { return 1; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int representation() { return 2; }

  using BreitWignerReichMooreBase::LRU;
  using BreitWignerReichMooreBase::LRF;

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
