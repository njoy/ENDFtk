/**
 *  @class
 *  @brief Base class for the unresolved resonance paraneters
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
template < Derived, LValue > class UnresolvedBase {

  /* fields */
  double spi_;
  double ap_;
  bool lssf_;

  std::vector< LValue > lvalues_;

protected:

    /* auxiliary functions */
    #include "ENDFtk/resonanceParameters/unresolved/UnresolvedBase/src/verifySize.hpp"

public:

  /* constructor */
  #include "ENDFtk/resonanceParameters/unresolved/UnresolvedBase/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int type() {

    return static_cast< const Derived* >( this )->LRU();
  }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int representation() {

    return static_cast< const Derived* >( this )->LRF();
  }

  /**
   *  @brief Return the average fission flag
   */
  constexpr int averageFissionWidthFlag() const {

    return static_cast< const Derived* >( this )->LFW();
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
   *  @brief Return the self-shielding only flag
   */
  bool LSSF() const { return this->lssf_; }

  /**
   *  @brief Return the self-shielding only flag
   */
  bool selfShieldingOnly() const { return this->LSSF(); }

  /**
   *  @brief Return the number of l values for which data is available
   */
  int NLS() const { return this->lvalues_.size(); }

  /**
   *  @brief Return the l value data
   */
  auto lValues() const { return ranges::view::all( this->lvalues_ ); }

  #include "ENDFtk/resonanceParameters/unresolved/UnresolvedBase/src/NC.hpp"
  #include "ENDFtk/resonanceParameters/unresolved/UnresolvedBase/src/print.hpp"
};
