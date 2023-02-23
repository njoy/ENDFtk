/**
 *  @class
 *  @brief General multi-level Breit-Wigner resonance parameter covariances
 *
 *  See ENDF102, section 32.2.2
 */
class GeneralMultiLevelBreitWigner :
  protected GeneralCovarianceBase<
                ShortRangeBreitWignerBlock,
                double,
                GeneralMultiLevelBreitWigner > {

  friend GeneralCovarianceBase<
             ShortRangeBreitWignerBlock,
             double,
             GeneralMultiLevelBreitWigner >;

protected:

  /* auxiliary functions */
  // blatantly taken from from GeneralSingleLevelBreitWigner
  #include "ENDFtk/section/32/151/GeneralSingleLevelBreitWigner/src/NC.hpp"
  #include "ENDFtk/section/32/151/GeneralSingleLevelBreitWigner/src/print.hpp"
  #include "ENDFtk/section/32/151/GeneralSingleLevelBreitWigner/src/read.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/32/151/GeneralMultiLevelBreitWigner/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int type() { return 1; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int representation() { return 2; }

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
