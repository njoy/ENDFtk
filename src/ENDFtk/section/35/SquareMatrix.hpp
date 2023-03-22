/**
 *  @class
 *  @brief NI-Type Sub-subsection with LB=7
 *
 *  See ENDF102, section 35.2 for more information.
 */
class SquareMatrix : protected ListRecord {

  #include "ENDFtk/section/35/SquareMatrix/src/verifyLB.hpp"

  // intentionally taken from File 33
  #include "ENDFtk/section/SquareMatrix/src/verifySize.hpp"
  #include "ENDFtk/section/SquareMatrix/src/generateList.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/35/SquareMatrix/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the lowest incident energy
   */
  int E1() const { return ListRecord::C1(); }

  /**
   *  @brief Return the lowest incident energy
   */
  int lowestEnergy() const { return this->E1(); }

  /**
   *  @brief Return the highest incident energy
   */
  int E2() const { return ListRecord::C2(); }

  /**
   *  @brief Return the highest incident energy
   */
  int highestEnergy() const { return this->E2(); }

  /**
   *  @brief Return the procedure type
   */
  int LB() const { return this->L2(); }

  /**
   *  @brief Return the procedure type
   */
  int procedure() const { return this->LB(); }

  /**
   *  @brief Return the number of values in this component
   */
  long NT() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the number of values in this component
   */
  long numberValues() const { return this->NT(); }

  /**
   *  @brief Return the number of energies in the array
   */
  long NE() const { return this->N2(); }

  /**
   *  @brief Return the number of energies in the array
   */
  long numberEnergies() const { return this->NE(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const {

    return ranges::views::take_exactly( ListRecord::list(),
                                        this->NE() );
  }

  /**
   *  @brief Return the matrix values
   */
  auto values() const {

    return ranges::views::drop_exactly( ListRecord::list(),
                                        this->NE() );
  }

  using ListRecord::NC;
  using ListRecord::print;

};
