#ifndef NJOY_ENDFTK_SECTION_SQUAREMATRIX
#define NJOY_ENDFTK_SECTION_SQUAREMATRIX

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
 *  @brief NI-Type Sub-subsection with LB=5
 *
 *  See ENDF102, section 33.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT SquareMatrix : protected ListRecord {

  #include "ENDFtk/section/SquareMatrix/src/verifyLB.hpp"
  #include "ENDFtk/section/SquareMatrix/src/verifySize.hpp"
  #include "ENDFtk/section/SquareMatrix/src/generateList.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/SquareMatrix/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the symmetry flag
   */
  int LS() const { return ListRecord::L1(); }

  /**
   *  @brief Return the symmetry flag
   */
  int symmetryFlag() const { return this->LS(); }

  /**
   *  @brief Return the symmetry flag as a boolean
   */
  bool isSymmetric() const { return this->LS(); }

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

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
