/**
 *  @class
 *  @brief Compact multi level Breit-Wigner resonance parameter covariances
 *
 *  See ENDF102, section 32.2.3.1
 */
class ENDFTK_PYTHON_EXPORT CompactMultiLevelBreitWigner :
  protected CompactCovarianceBase<
                CompactBreitWignerUncertainties,
                double,
                CompactMultiLevelBreitWigner > {

  friend CompactCovarianceBase<
             CompactBreitWignerUncertainties,
             double,
             CompactMultiLevelBreitWigner >;

protected:

  /* auxiliary functions */
  // blatantly taken from CompactSingleLevelBreitWigner
  #include "ENDFtk/section/32/151/CompactSingleLevelBreitWigner/src/NC.hpp"
  #include "ENDFtk/section/32/151/CompactSingleLevelBreitWigner/src/print.hpp"
  #include "ENDFtk/section/32/151/CompactSingleLevelBreitWigner/src/read.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/32/151/CompactMultiLevelBreitWigner/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int type() { return 1; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int representation() { return 2; }

  using CompactCovarianceBase::LRU;
  using CompactCovarianceBase::LRF;
  using CompactCovarianceBase::LFW;
  using CompactCovarianceBase::averageFissionWidthFlag;
  using CompactCovarianceBase::LCOMP;
  using CompactCovarianceBase::covarianceRepresentation;

  using CompactCovarianceBase::SPI;
  using CompactCovarianceBase::spin;
  using CompactCovarianceBase::AP;
  using CompactCovarianceBase::scatteringRadius;
  using CompactCovarianceBase::DAP;
  using CompactCovarianceBase::scatteringRadiusUncertainty;
  using CompactCovarianceBase::ISR;
  using CompactCovarianceBase::scatteringRadiusUncertaintyFlag;
  using CompactCovarianceBase::uncertainties;
  using CompactCovarianceBase::correlationMatrix;

  using CompactCovarianceBase::NC;
  using CompactCovarianceBase::print;
};
