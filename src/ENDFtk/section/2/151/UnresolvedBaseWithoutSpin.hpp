// Forward declaration of the LJValueType struct
//
// The following code does not compile in gcc when declared inside a
// class/struct (it used to compile when it was in the resonanceParameters
// namespace):
//  template < typename T > struct LJValueType {};
//  class UnresolvedEnergyDependent;
//  template<> struct LJValueType< UnresolvedEnergyDependent > { /* stuff */ };
//
// gcc compilers only allow for explicit template specialisation inside a
// namespace scope, not inside a class/struct as is the case here (inside the
// ENDFtk::section::Type< 2, 151 > class).
//
// Using a dummy defaulted template argument is a well known trick to get
// around this issue in gcc. llvm compilers do not have this issue.
template < typename T, typename GCC = void >
struct LJValueType {};

/**
 *  @class
 *  @brief Base class for the unresolved resonance parameters
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
  #include "ENDFtk/section/2/151/UnresolvedBaseWithoutSpin/src/verifySize.hpp"

  /* constructor */
  #include "ENDFtk/section/2/151/UnresolvedBaseWithoutSpin/src/ctor.hpp"

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
   *  @brief Return the number of l values for which data is available
   */
  int numberLValues() const { return this->NLS(); }

  /**
   *  @brief Return the l value data
   */
  auto lValues() const { return ranges::view::all( this->lvalues_ ); }
};
