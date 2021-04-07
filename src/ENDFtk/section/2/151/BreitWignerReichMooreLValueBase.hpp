/**
 *  @class
 *  @brief Base class for Breit-Wigner and Reich-Moore resonance parameters for
 *         a given l value
 *
 *  See ENDF102, section 2.2.1.1 and 2.2.1.2 for more information.
 */
class BreitWignerReichMooreLValueBase : protected ListRecord {

public:

  using Column = StrideRange< DropRange< AllRange< double > > >;

private:

  /* auxiliary functions */
  #include "ENDFtk/section/2/151/BreitWignerReichMooreLValueBase/src/verifySize.hpp"
  #include "ENDFtk/section/2/151/BreitWignerReichMooreLValueBase/src/generateList.hpp"

  Column column( unsigned int i ) const {

    return ListRecord::list() | ranges::views::drop_exactly( i )
                              | ranges::views::stride( 6 );
  }

protected:

  /* constructor */
  #include "ENDFtk/section/2/151/BreitWignerReichMooreLValueBase/src/ctor.hpp"

  /**
   *  @brief Return the first width
   */
  Column G1() const { return BreitWignerReichMooreLValueBase::column( 2 ); }

  /**
   *  @brief Return the second width
   */
  Column G2() const { return BreitWignerReichMooreLValueBase::column( 3 ); }

  /**
   *  @brief Return the third width
   */
  Column G3() const { return BreitWignerReichMooreLValueBase::column( 4 ); }

  /**
   *  @brief Return the fourth width
   */
  Column G4() const { return BreitWignerReichMooreLValueBase::column( 5 ); }

  /**
   *  @brief Return the resonances
   */
  ChunkRange< AllRange< double > > resonances() const {

    return ListRecord::list() | ranges::views::chunk(6);
  }

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
  Column ER() const { return BreitWignerReichMooreLValueBase::column( 0 ); }

  /**
  *  @brief Return the resonance energies
   */
  Column resonanceEnergies() const { return this->ER(); }

  /**
   *  @brief Return the spin values
   */
  Column AJ() const { return BreitWignerReichMooreLValueBase::column( 1 ); }

  /**
  *  @brief Return the spin values
   */
  Column spinValues() const { return this->AJ(); }

  using ListRecord::NC;
  using ListRecord::print;
};
