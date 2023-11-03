/**
 *  @class
 *  @brief Covariance data for the unresolved resonances
 *
 *  See ENDF102, section 32.2.4 for more information.
 */
class CovarianceMatrix : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/32/151/UnresolvedRelativeCovariances/CovarianceMatrix/src/verifySize.hpp"
  #include "ENDFtk/section/32/151/UnresolvedRelativeCovariances/CovarianceMatrix/src/generateList.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/32/151/UnresolvedRelativeCovariances/CovarianceMatrix/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the number of average parameters for which covariance data
   *         is given
   */
  int MPAR() const { return ListRecord::L1(); }

  /**
   *  @brief Return the number of average parameters for which covariance data
   *         is given
   */
  int numberAverageParameters() const { return this->MPAR(); }

  /**
   *  @brief Return the order of the covariance matrix
   */
  int NPAR() const { return ListRecord::N2(); }

  /**
   *  @brief Return the order of the covariance matrix
   */
  int covarianceMatrixOrder() const { return this->NPAR(); }

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
