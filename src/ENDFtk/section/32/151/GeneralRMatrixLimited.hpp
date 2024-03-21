/**
 *  @class
 *  @brief General R-matrix limited resonance parameter covariances
 *
 *  See ENDF102, section 32.2.2
 */
class ENDFTK_PYTHON_EXPORT GeneralRMatrixLimited :
  protected GeneralCovarianceBase<
                ShortRangeRMatrixLimitedBlock,
                ReichMooreScatteringRadiusUncertainties,
                GeneralRMatrixLimited > {

  friend GeneralCovarianceBase<
             ShortRangeRMatrixLimitedBlock,
             ReichMooreScatteringRadiusUncertainties,
             GeneralRMatrixLimited >;

protected:

  /* auxiliary functions */
  #include "ENDFtk/section/32/151/GeneralRMatrixLimited/src/NC.hpp"
  #include "ENDFtk/section/32/151/GeneralRMatrixLimited/src/print.hpp"
  #include "ENDFtk/section/32/151/GeneralRMatrixLimited/src/read.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/32/151/GeneralRMatrixLimited/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int type() { return 1; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int representation() { return 7; }

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

  using GeneralCovarianceBase::NC;
  using GeneralCovarianceBase::print;
};
