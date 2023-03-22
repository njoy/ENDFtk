/**
 *  @class
 *  @brief Covariance data for the R-matrix limited resonance data
 *
 *  See ENDF102, section 32.2.2 for more information.
 */
class CovarianceMatrix : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/32/151/ShortRangeRMatrixLimitedBlock/CovarianceMatrix/src/verifySize.hpp"
  #include "ENDFtk/section/32/151/ShortRangeRMatrixLimitedBlock/CovarianceMatrix/src/generateList.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/32/151/ShortRangeRMatrixLimitedBlock/CovarianceMatrix/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the order of the covariance matrix
   */
  int NPARB() const { return ListRecord::N2(); }

  /**
   *  @brief Return the order of the covariance matrix
   */
  int covarianceMatrixOrder() const { return this->NPARB(); }

  /**
   *  @brief Return the number of values in the upper triangular covariance matrix
   */
  int NVS() const {

    return this->covarianceMatrixOrder()
           * ( this->covarianceMatrixOrder() + 1 ) / 2 ;
  }

  /**
   *  @brief Return the number of resonances for this l value
   */
  int numberValues() const { return this->NVS(); }

  /**
   *  @brief Return the upper triangular covariance matrix
   */
  auto covarianceMatrix() const {

    return ListRecord::list();
  }

  //! @todo provide convenience interface for the covariance data

  using ListRecord::NC;
  using ListRecord::print;
};
