/**
 *  @class
 *  @brief Base class for Breit-Wigner and Reich-Moore resonance parameters for
 *         a given l value
 *
 *  See ENDF102, section 2.2.1.1 and 2.2.1.2 for more information.
 */
class BreitWignerReichMooreLValueBase : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/resonanceParameters/resolved/BreitWignerReichMooreLValueBase/src/verifySize.hpp"
  #include "ENDFtk/resonanceParameters/resolved/BreitWignerReichMooreLValueBase/src/generateList.hpp"

protected:

  /* constructor */
  #include "ENDFtk/resonanceParameters/resolved/BreitWignerReichMooreLValueBase/src/ctor.hpp"

public:

  /* get methods */

  /**
   *  @brief Return the atomic weight ratio of the current isotope to the
   *         neutron mass
   */
  double AWRI() const { return ListRecord::C1(); }

  /**
   *  @brief Return the atomic weight ratio of the current isotope to the
   *         neutron mass
   */
  double atomicWeightRatio() const { return this->AWRI(); }

  using ListRecord::C2;

  /**
   *  @brief Return the value of the orbital momentum l
   */
  int L() const { return ListRecord::L1(); }

  /**
   *  @brief Return the value of the orbital momentum l
   */
  int orbitalMomentum() const { return this->L(); }

  using ListRecord::L2;

  /**
   *  @brief Return the number of resonances for this l value
   */
  int NRS() const { return ListRecord::N2(); }

  /**
   *  @brief Return the number of resonances for this l value
   */
  int numberResonances() const { return this->NRS(); }

  /**
   *  @brief Return the resonance energies
   */
  auto ER() const { return ListRecord::list() | ranges::view::stride( 6 ); }

  /**
  *  @brief Return the resonance energies
   */
  auto resonanceEnergies() const { return this->ER(); }

  /**
   *  @brief Return the spin values
   */
  auto AJ() const {

    return ListRecord::list() | ranges::view::drop_exactly( 1 )
                              | ranges::view::stride( 6 ); }

  /**
  *  @brief Return the spin values
   */
  auto spinValues() const { return this->AJ(); }

  /**
   *  @brief Return the first width
   */
  auto G1() const {

    return ListRecord::list() | ranges::view::drop_exactly( 2 )
                              | ranges::view::stride( 6 ); }

  /**
   *  @brief Return the second width
   */
  auto G2() const {

    return ListRecord::list() | ranges::view::drop_exactly( 3 )
                              | ranges::view::stride( 6 ); }

  /**
   *  @brief Return the third width
   */
  auto G3() const {

    return ListRecord::list() | ranges::view::drop_exactly( 4 )
                              | ranges::view::stride( 6 ); }

  /**
   *  @brief Return the fourth width
   */
  auto G4() const {

    return ListRecord::list() | ranges::view::drop_exactly( 5 )
                              | ranges::view::stride( 6 ); }

  /**
   *  @brief Return the resonances
   */
  auto resonances() const {

    return ListRecord::list() | ranges::view::chunk(6);
  }

  using ListRecord::NC;
  using ListRecord::print;
};

