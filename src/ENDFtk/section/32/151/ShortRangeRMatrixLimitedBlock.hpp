/**
 *  @class
 *  @brief Short-range limited R-matrix resonance parameters and covariance data
 *
 *  See ENDF102, section 32.2.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT ShortRangeRMatrixLimitedBlock {

public:

  #include "ENDFtk/section/32/151/ShortRangeRMatrixLimitedBlock/ResonanceParameters.hpp"
  #include "ENDFtk/section/32/151/ShortRangeRMatrixLimitedBlock/CovarianceMatrix.hpp"

private:

  /* fields */
  std::vector< ResonanceParameters > parameters_;
  CovarianceMatrix covariance_;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ENDFtk/section/32/151/ShortRangeRMatrixLimitedBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of spin groups for which resonance parameters
   *         are given
   */
  int NJSX() const { return this->parameters_.size(); }

  /**
   *  @brief Return the number of spin groups for which resonance parameters
   *         are given
   */
  int numberSpinGroups() const { return this->NJSX(); }

  /**
   *  @brief Return the resonance parameters
   */
  auto resonanceParameters() const {

    using namespace njoy::tools;
    return this->parameters_ | std20::views::all;
  }

  /**
   *  @brief Return the covariance matrix
   */
  const CovarianceMatrix& covarianceMatrix() const {

    return this->covariance_;
  }

  #include "ENDFtk/section/32/151/ShortRangeRMatrixLimitedBlock/src/NC.hpp"
  #include "ENDFtk/section/32/151/ShortRangeRMatrixLimitedBlock/src/print.hpp"
};
