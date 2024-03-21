#ifndef NJOY_ENDFTK_SECTION_RECTANGULARMATRIX
#define NJOY_ENDFTK_SECTION_RECTANGULARMATRIX

// system includes

// other includes
#include "ENDFtk/macros.hpp"
#include "range/v3/range/conversion.hpp"
#include "range/v3/view/concat.hpp"
#include "range/v3/view/drop_exactly.hpp"
#include "range/v3/view/take_exactly.hpp"
#include "ENDFtk/ListRecord.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

/**
 *  @class
 *  @brief NI-Type Sub-subsection with LB=6
 *
 *  See ENDF102, section 33.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT RectangularMatrix : protected ListRecord {

  #include "ENDFtk/section/RectangularMatrix/src/verifyLB.hpp"
  #include "ENDFtk/section/RectangularMatrix/src/verifySize.hpp"
  #include "ENDFtk/section/RectangularMatrix/src/generateList.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/RectangularMatrix/src/ctor.hpp"

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

    return ranges::views::take_exactly( ListRecord::list(), this->NER() );
  }

  /**
   *  @brief Return the row energy values
   */
  auto columnEnergies() const {

    return ranges::views::drop_exactly( ListRecord::list(), this->NER() );
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

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
