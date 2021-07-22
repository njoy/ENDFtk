/**
 *  @class
 *  @brief NI-Type Sub-subsection with LB=6
 *
 *  See ENDF102, section 33.2 for more information.
 */
class RectangularMatrix : protected ListRecord {

  #include "ENDFtk/section/33/RectangularMatrix/src/verifyLB.hpp"
  #include "ENDFtk/section/33/RectangularMatrix/src/verifySize.hpp"
  #include "ENDFtk/section/33/RectangularMatrix/src/generateList.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/33/RectangularMatrix/src/ctor.hpp"

  /* methods */

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
   *  @brief Return the number of energies representing a row
   */
  long NER() const { return this->N2(); }

  /**
   *  @brief Return the number of energies representing a row
   */
  long numberRowEnergies() const { return this->NER(); }

  /**
   *  @brief Return the number of energies representing a column
   */
  long NEC() const { return ( this->NT() - 1 ) / this->NER(); }

  /**
   *  @brief Return the number of energies representing a column
   */
  long numberColumnEnergies() const { return this->NEC(); }

  /**
   *  @brief Return the row energy values
   */
  auto rowEnergies() const {

    return ranges::views::take_exactly( ListRecord::list(),
                                        this->NER() );
  }

  /**
   *  @brief Return the row energy values
   */
  auto columnEnergies() const {

    return ranges::views::drop_exactly( ListRecord::list(),
                                        this->NER() );
  }

  /**
   *  @brief Return the matrix values
   */
  auto values() const {

    return ranges::views::drop_exactly( ListRecord::list(),
                                        this->NER() + this->NEC() );
  }

  using ListRecord::NC;
  using ListRecord::print;

};
