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
class UnresolvedRelativeCovariances {

public:

  #include "ENDFtk/section/32/151/UnresolvedRelativeCovariances/JValue.hpp"
  #include "ENDFtk/section/32/151/UnresolvedRelativeCovariances/LValue.hpp"
//  #include "ENDFtk/section/32/151/UnresolvedRelativeCovariances/CovarianceMatrix.hpp"

private:

  /* fields */
  double spi_;
  double ap_;
  std::vector< LValue > lvalues_;
//  CovarianceMatrix matrix_;

  /* auxiliary functions */

protected:

  /* constructor */
//  #include "ENDFtk/section/32/151/CompactCovarianceBase/src/ctor.hpp"

public:

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
  static constexpr bool LFW() { return false; }

  /**
  *  @brief Return the average fission flag
  */
  constexpr int averageFissionWidthFlag() const {

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
   *  @brief Return the resonance parameter uncertainties
   */
  auto lValues() const {

    return ranges::cpp20::views::all( this->lvalues_ );
  }

//  /**
//   *  @brief Return the correlation matrix
//   */
//  const CovarianceMatrix& covarianceMatrix() const {
//
//    return this->matrix_;
//  }

//  #include "ENDFtk/section/32/151/UnresolvedRelativeCovariances/src/NC.hpp"
//  #include "ENDFtk/section/32/151/UnresolvedRelativeCovariances/src/print.hpp"
};
