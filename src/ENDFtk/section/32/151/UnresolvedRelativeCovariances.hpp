/**
 *  @class
 *  @brief Unresolved resonance relative covariance data
 *
 *  The UnresolvedRelativeCovariances class is used to represent the covariance
 *  data in the unresolved resonance region. It is the ONLY unresolved resonance
 *  representation thus far.
 *
 *  See ENDF102, section 32.2.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT UnresolvedRelativeCovariances {

public:

  #include "ENDFtk/section/32/151/UnresolvedRelativeCovariances/JValue.hpp"
  #include "ENDFtk/section/32/151/UnresolvedRelativeCovariances/LValue.hpp"
  #include "ENDFtk/section/32/151/UnresolvedRelativeCovariances/CovarianceMatrix.hpp"

private:

  /* fields */
  double spi_;
  double ap_;
  std::vector< LValue > lvalues_;
  CovarianceMatrix matrix_;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ENDFtk/section/32/151/UnresolvedRelativeCovariances/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int LRU() { return 2; }

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  constexpr int type() const { return this->LRU(); }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int LRF() { return 1; }

  /**
   *  @brief Return the resonance representation
   */
  constexpr int representation() const { return this->LRF(); }

  /**
   *  @brief Return the average fission flag
   */
  bool LFW() const {

    return this->covarianceMatrix().MPAR() < 5 ? false : true;
  }

  /**
  *  @brief Return the average fission flag
  */
  bool averageFissionWidthFlag() const {

    return this->LFW();
  }

  /**
   *  @brief Return the target spin
   */
  double SPI() const { return this->spi_; }

  /**
   *  @brief Return the target spin
   */
  double spin() const { return this->SPI(); }

  /**
   *  @brief Return the scattering radius
   */
  double AP() const { return this->ap_; }

  /**
   *  @brief Return the scattering radius
   */
  double scatteringRadius() const { return this->AP(); }

  /**
   *  @brief Return the number of l values for which data is available
   */
  int NLS() const { return this->lvalues_.size(); }

  /**
   *  @brief Return the number of l values for which data is available
   */
  int numberLValues() const { return this->NLS(); }

  /**
   *  @brief Return the resonance parameter uncertainties
   */
  auto lValues() const {

    using namespace njoy::tools;
    return this->lvalues_ | std20::views::all;
  }

  /**
   *  @brief Return the covariance matrix
   */
  const CovarianceMatrix& covarianceMatrix() const {

    return this->matrix_;
  }

  #include "ENDFtk/section/32/151/UnresolvedRelativeCovariances/src/NC.hpp"
  #include "ENDFtk/section/32/151/UnresolvedRelativeCovariances/src/print.hpp"
};
