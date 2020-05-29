template < typename T >
struct LJValueType {};

/**
 *  @class
 *  @brief Base class for the unresolved resonance paraneters
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
template < typename Derived,
           typename LValue = typename LJValueType< Derived >::LType >
class UnresolvedBaseWithoutSpin {

  /* fields */
  std::vector< LValue > lvalues_;

protected:

  /* auxiliary functions */
  #include "ENDFtk/resonanceParameters/unresolved/UnresolvedBaseWithoutSpin/src/readLValues.hpp"
  #include "ENDFtk/resonanceParameters/unresolved/UnresolvedBaseWithoutSpin/src/verifySize.hpp"

  /* constructor */
  #include "ENDFtk/resonanceParameters/unresolved/UnresolvedBaseWithoutSpin/src/ctor.hpp"

public:

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  int type() const {

    return static_cast< const Derived* >( this )->LRU();
  }

  /**
   *  @brief Return the resonance representation
   */
  int representation() const {

    return static_cast< const Derived* >( this )->LRF();
  }

  /**
   *  @brief Return the average fission flag
   */
  int averageFissionWidthFlag() const {

    return static_cast< const Derived* >( this )->LFW();
  }

  /**
   *  @brief Return the target spin
   */
  double spin() const {

    return static_cast< const Derived* >( this )->SPI();
  }

  /**
   *  @brief Return the scattering radius
   */
  double scatteringRadius() const {

    return static_cast< const Derived* >( this )->AP();
  }

  /**
   *  @brief Return the self-shielding only flag
   */
  bool selfShieldingOnly() const {

    return static_cast< const Derived* >( this )->LSSF();
  }

  /**
   *  @brief Return the number of l values for which data is available
   */
  int NLS() const { return this->lvalues_.size(); }

  /**
   *  @brief Return the l value data
   */
  auto lValues() const { return ranges::view::all( this->lvalues_ ); }
};
