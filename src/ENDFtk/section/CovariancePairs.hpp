#ifndef NJOY_ENDFTK_SECTION_COVARIANCEPAIRS
#define NJOY_ENDFTK_SECTION_COVARIANCEPAIRS

// system includes

// other includes
#include "ENDFtk/macros.hpp"
#include "range/v3/view/drop_exactly.hpp"
#include "range/v3/view/take_exactly.hpp"
#include "range/v3/view/stride.hpp"
#include "ENDFtk/ListRecord.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

/**
 *  @class
 *  @brief NI-Type Sub-subsection with LB=0,1,2,3,4,8,9
 *
 *  See ENDF102, section 33.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT CovariancePairs : protected ListRecord {

  #include "ENDFtk/section/CovariancePairs/src/verifyLB.hpp"
  #include "ENDFtk/section/CovariancePairs/src/verifySize.hpp"
  #include "ENDFtk/section/CovariancePairs/src/generateList.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/CovariancePairs/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of pairs in the second array
   */
  int LT() const { return ListRecord::L1(); }

  /**
   *  @brief Return the number of pairs in the second array
   */
  int numberSecondPairs() const { return this->LT(); }

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
   *  @brief Return the total number of pairs
   */
  long NP() const { return this->NT()/2; }

  /**
   *  @brief Return the total number of pairs
   */
  long numberPairs() const { return this->NP(); }

  /**
   *  @brief Return the energy values from the first array
   */
  auto EK() const {
    return ranges::views::take_exactly( ListRecord::list(),
                                       2 * ( this->NP() - this->LT() ) )
            | ranges::views::stride( 2 );
  }

  /**
   *  @brief Return the energy values from the first array
   */
  auto firstArrayEnergies() const { return this->EK(); }

  /**
   *  @brief Return the F values from the first array
   */
  auto FK() const {
    return ranges::views::take_exactly( ListRecord::list(),
                                       2 * ( this->NP() - this->LT() ) )
            | ranges::views::drop_exactly( 1 )
            | ranges::views::stride( 2 );
  }

  /**
   *  @brief Return the F values from the first array
   */
  auto firstArrayFValues() const { return this->FK(); }

  /**
   *  @brief Return the energy values from the second array
   */
  auto EL() const {
    return ranges::views::drop_exactly( ListRecord::list(),
                                       2 * ( this->NP() - this->LT() ) )
            | ranges::views::stride( 2 );
  }

  /**
   *  @brief Return the energy values from the second array
   */
  auto secondArrayEnergies() const { return this->EL(); }

  /**
   *  @brief Return the F values from the second array
   */
  auto FL() const {
    return ranges::views::drop_exactly( ListRecord::list(),
                                       2 * ( this->NP() - this->LT() ) + 1 )
            | ranges::views::stride( 2 );
  }

  /**
   *  @brief Return the F values from the second array
   */
  auto secondArrayFValues() const { return this->FL(); }

  using ListRecord::NC;
  using ListRecord::print;
};

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
