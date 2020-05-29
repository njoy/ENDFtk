/**
 *  @class
 *  @brief Base class for the unresolved resonance paraneters
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
template < typename Derived,
           typename LValue = typename LJValueType< Derived >::LType >
class UnresolvedBase : public UnresolvedBaseWithoutSpin< Derived, LValue > {

  /* fields */
  double spi_;
  double ap_;
  bool lssf_;

protected:

  /* constructor */
  #include "ENDFtk/resonanceParameters/unresolved/UnresolvedBase/src/ctor.hpp"

  using UnresolvedBaseWithoutSpin< Derived >::readLValues;

public:

  /* get methods */

  /**
   *  @brief Return the target spin
   */
  double SPI() const { return this->spi_; }

  /**
   *  @brief Return the scattering radius
   */
  double AP() const { return this->ap_; }

  /**
   *  @brief Return the self-shielding only flag
   */
  bool LSSF() const { return this->lssf_; }

  using UnresolvedBaseWithoutSpin< Derived >::type;
  using UnresolvedBaseWithoutSpin< Derived >::representation;
  using UnresolvedBaseWithoutSpin< Derived >::averageFissionWidthFlag;
  using UnresolvedBaseWithoutSpin< Derived >::spin;
  using UnresolvedBaseWithoutSpin< Derived >::scatteringRadius;
  using UnresolvedBaseWithoutSpin< Derived >::selfShieldingOnly;
  using UnresolvedBaseWithoutSpin< Derived >::NLS;
  using UnresolvedBaseWithoutSpin< Derived >::lValues;

  #include "ENDFtk/resonanceParameters/unresolved/UnresolvedBase/src/NC.hpp"
  #include "ENDFtk/resonanceParameters/unresolved/UnresolvedBase/src/print.hpp"
};
