/**
 *  @class
 *  @brief General Reich-Moore resonance parameter covariances
 *
 *  See ENDF102, section 32.2.2
 */
class GeneralReichMoore :
  protected GeneralCovarianceBase<
                ShortRangeReichMooreBlock,
                ReichMooreScatteringRadiusUncertainties,
                GeneralReichMoore > {

  friend GeneralCovarianceBase<
             ShortRangeReichMooreBlock,
             ReichMooreScatteringRadiusUncertainties,
             GeneralReichMoore >;

protected:

  /* auxiliary functions */
  #include "ENDFtk/section/32/151/GeneralReichMoore/src/NC.hpp"
  #include "ENDFtk/section/32/151/GeneralReichMoore/src/print.hpp"
  #include "ENDFtk/section/32/151/GeneralReichMoore/src/read.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/32/151/GeneralReichMoore/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int type() { return 1; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int representation() { return 3; }

  using GeneralCovarianceBase::LRU;
  using GeneralCovarianceBase::LRF;
  using GeneralCovarianceBase::LFW;
  using GeneralCovarianceBase::averageFissionWidthFlag;
  using GeneralCovarianceBase::LCOMP;
  using GeneralCovarianceBase::covarianceRepresentation;

  using GeneralCovarianceBase::AWRI;
  using GeneralCovarianceBase::atomicWeightRatio;
  using GeneralCovarianceBase::SPI;
  using GeneralCovarianceBase::spin;
  using GeneralCovarianceBase::AP;
  using GeneralCovarianceBase::scatteringRadius;
  using GeneralCovarianceBase::NLS;
  using GeneralCovarianceBase::numberLValues;
  using GeneralCovarianceBase::DAP;
  using GeneralCovarianceBase::scatteringRadiusUncertainty;
  using GeneralCovarianceBase::NSRS;
  using GeneralCovarianceBase::numberShortRangeBlocks;
  using GeneralCovarianceBase::NLRS;
  using GeneralCovarianceBase::numberLongRangeBlocks;
  using GeneralCovarianceBase::ISR;
  using GeneralCovarianceBase::scatteringRadiusUncertaintyFlag;
  using GeneralCovarianceBase::shortRangeBlocks;
  using GeneralCovarianceBase::longRangeBlocks;

  using GeneralCovarianceBase::NC;
  using GeneralCovarianceBase::print;
};
