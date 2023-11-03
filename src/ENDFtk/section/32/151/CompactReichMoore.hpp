/**
 *  @class
 *  @brief Compact Reich-Moore resonance parameter covariances
 *
 *  See ENDF102, section 32.2.3.2
 */
class CompactReichMoore :
  protected CompactCovarianceBase<
                CompactReichMooreUncertainties,
                ReichMooreScatteringRadiusUncertainties,
                CompactReichMoore > {

  friend CompactCovarianceBase<
             CompactReichMooreUncertainties,
             ReichMooreScatteringRadiusUncertainties,
             CompactReichMoore >;

protected:

  /* auxiliary functions */
  #include "ENDFtk/section/32/151/CompactReichMoore/src/NC.hpp"
  #include "ENDFtk/section/32/151/CompactReichMoore/src/print.hpp"
  #include "ENDFtk/section/32/151/CompactReichMoore/src/read.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/32/151/CompactReichMoore/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int type() { return 1; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int representation() { return 3; }

  /**
   *  @brief Return the angular distribution flag
   */
  bool LAD() const { return CompactCovarianceBase::L1(); }

  /**
   *  @brief Return the angular distribution flag
   */
  bool angularDistributionsFlag() const { return this->LAD(); }

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
