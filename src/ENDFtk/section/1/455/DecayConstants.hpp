/**
 *  @class
 *  @brief Decay constants for delayed neutron precursors at a given incident
 *         energy
 *
 *  See ENDF102, section 1.3 for more information.
 */
class ENDFTK_PYTHON_EXPORT DecayConstants : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/1/455/DecayConstants/src/generateList.hpp"
  #include "ENDFtk/section/1/455/DecayConstants/src/verifySize.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/1/455/DecayConstants/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of delayed neutron precursors
   */
  int NNF() const { return ListRecord::NPL() / 2; }

  /**
   *  @brief Return the number of delayed neutron precursors
   */
  int numberPrecursors() const { return this->NNF(); }

  /**
   *  @brief Return the incident energy value
   */
  double E() const { return ListRecord::C2(); }

  /**
   *  @brief Return the incident energy value
   */
  double incidentEnergy() const { return this->E(); }

  /**
   *  @brief Return the decay constants
   */
  auto lambdas() const {

    using namespace njoy::tools;
    return ListRecord::list() | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the decay constants
   */
  auto decayConstants() const {

    return this->lambdas();
  }

  /**
   *  @brief Return the abundance values
   */
  auto alphas() const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( 1 )
                              | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the abundance values
   */
  auto abundances() const {

    return this->alphas();
  }

  using ListRecord::NC;
  using ListRecord::print;
};
