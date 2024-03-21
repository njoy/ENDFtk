#ifndef NJOY_ENDFTK_SECTION_DERIVEDREDUNDANT
#define NJOY_ENDFTK_SECTION_DERIVEDREDUNDANT

// system includes

// other includes
#include "ENDFtk/macros.hpp"
#include "range/v3/view/drop_exactly.hpp"
#include "range/v3/view/stride.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

/**
 *  @class
 *  @brief NC-Type Sub-subsection with LTY=0
 *
 *  See ENDF102, section 33.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT DerivedRedundant {

   /* fields */
   ListRecord list_;

   /* auxiliary functions */
   #include "ENDFtk/section/DerivedRedundant/src/verifyLTY.hpp"
   #include "ENDFtk/section/DerivedRedundant/src/generateList.hpp"

 public:

  /* constructor */
  #include "ENDFtk/section/DerivedRedundant/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the procedure
   */
  static constexpr int LTY() { return 0; }

  /**
   *  @brief Return the procedure
   */
  int procedure() const { return this->LTY(); }

  /**
   *  @brief Return the lower energy bound
   */
  double E1() const { return this->list_.C1(); }

  /**
   *  @brief Return the lower energy bound
   */
  double lowerEnergy() const { return this->E1(); }

  /**
   *  @brief Return the upper energy bound
   */
  double E2() const { return this->list_.C2(); }

  /**
   *  @brief Return the upper energy bound
   */
  double upperEnergy() const { return this->E2(); }

  /**
   *  @brief Return the number of reactions
   */
  int NCI() const { return this->list_.N2(); }

  /**
   *  @brief Return the number of reactions
   */
  int numberReactions() const { return this->NCI(); }

  /**
   *  @brief Return the coefficients
   */
  auto CI() const { return ranges::views::stride(this->list_.list(), 2); }

  /**
   *  @brief Return the coefficients
   */
  auto coefficients() const { return this->CI(); }

  /**
   *  @brief Return the reaction MTs
   */
  auto XMTI() const {

   return ranges::views::drop_exactly(this->list_.list(), 1)
      | ranges::views::stride(2);
  }

  /**
   *  @brief Return the reaction MTs
   */
  auto reactions() const { return this->XMTI(); }

  #include "ENDFtk/section/DerivedRedundant/src/NC.hpp"
  #include "ENDFtk/section/DerivedRedundant/src/print.hpp"

};

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
