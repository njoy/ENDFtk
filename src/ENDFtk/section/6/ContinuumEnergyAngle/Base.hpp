/**
 *  @class
 *  @brief Base class for legendre, tabulated and Kalbach-Mann distributions
 *
 *  See ENDF102, section 6.2.3.1 for more information.
 */
class Base : protected ListRecord {

public:

  /* methods */

  /**
   *  @brief Return the incident energy for which the angular distribution
   *         is given
   */
  double E() const { return ListRecord::C2(); }

  /**
   *  @brief Return the incident energy for which the angular distribution
   *         is given
   */
  double incidentEnergy() const { return this->E(); }

  /**
   *  @brief Return the number of discrete energies
   */
  long ND() const { return ListRecord::L1(); }

  /**
   *  @brief Return the number of discrete energies
   */
  long numberDiscreteEnergies() const { return this->ND(); }

  /**
   *  @brief Return the number of angular parameter values
   */
  long NA() const { return ListRecord::L2(); }

  /**
   *  @brief Return the number of angular parameter values
   */
  long numberAngularParameters() const { return this->NA(); }

  /**
   *  @brief Return the number of values
   */
  long NW() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the number of secondary energy values
   */
  long NEP() const { return ListRecord::N2(); }

  /**
   *  @brief Return the number of secondary energy values
   */
  long numberSecondaryEnergies() const { return this->NEP(); }

  /**
   *  @brief Return the secondary energy values
   */
  auto EP() const {

    using namespace njoy::tools;
    return ListRecord::list() | std23::views::stride( 2 + this->NA() );
  }

  /**
   *  @brief Return the secondary energy values
   */
  auto energies() const { return this->EP(); }

  /**
   *  @brief Return the total emission probabilities
   */
  auto F0() const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( 1 )
                              | std23::views::stride( 2 + this->NA() );
  }

  /**
   *  @brief Return the total emission probabilities
   */
  auto
  totalEmissionProbabilities() const {

    return this->F0();
  }

private:

  /* auxiliary functions */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/Base/src/verifySize.hpp"

protected:

  /* constructor */
  #include "ENDFtk/section/6/ContinuumEnergyAngle/Base/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the data
   */
  auto data() const {

    using namespace njoy::tools;
    return ListRecord::list()
               | std23::views::chunk( 2 + this->NA() )
               | std20::views::transform( [] ( auto&& chunk )
                                             { return chunk | std20::views::drop( 1 ); } );
  }

public:

  using ListRecord::NC;
  using ListRecord::print;
};
