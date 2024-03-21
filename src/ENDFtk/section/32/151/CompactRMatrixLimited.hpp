/**
 *  @class
 *  @brief Compact R-matrix limited resonance parameter covariances
 *
 *  See ENDF102, section 32.2.3.2
 */
class ENDFTK_PYTHON_EXPORT CompactRMatrixLimited :
  protected CompactCovarianceBase<
                CompactRMatrixLimitedUncertainties,
                ReichMooreScatteringRadiusUncertainties,
                CompactRMatrixLimited > {

  friend CompactCovarianceBase<
             CompactRMatrixLimitedUncertainties,
             ReichMooreScatteringRadiusUncertainties,
             CompactRMatrixLimited >;

protected:

  /* auxiliary functions */
  #include "ENDFtk/section/32/151/CompactRMatrixLimited/src/NC.hpp"
  #include "ENDFtk/section/32/151/CompactRMatrixLimited/src/print.hpp"
  #include "ENDFtk/section/32/151/CompactRMatrixLimited/src/read.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/32/151/CompactRMatrixLimited/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int type() { return 1; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int representation() { return 7; }

  /**
   *  @brief Return whether or not the widths are reduced or not
   */
  bool IFG() const { return CompactCovarianceBase::L1(); }

  /**
   *  @brief Return whether or not the widths are reduced or not
   */
  bool reducedWidths() const { return this->IFG(); }

  /**
   *  @brief Return the number of spin groups
   */
  unsigned int NJS() const { return CompactCovarianceBase::N1(); }

  /**
   *  @brief Return the number of spin groups
   */
  unsigned int numberSpinGroups() const { return this->NJS(); }

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
