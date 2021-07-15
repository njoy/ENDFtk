#ifndef NJOY_ENDFTK_SECTION_28
#define NJOY_ENDFTK_SECTION_28

// system includes

// other includes
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section.hpp"
#include "range/v3/view/chunk.hpp"
#include "range/v3/view/drop_exactly.hpp"
#include "range/v3/view/stride.hpp"
#include "range/v3/view/transform.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief MF28 - atomic relaxation data
   *
   *  See ENDF102, section 28.2 for more information.
   */
  template<>
  class Type< 28 > : protected Base {

  public:

    #include "ENDFtk/section/28/SubshellData.hpp"

  private:

    /* fields */
    std::vector< SubshellData > subshells_;

  public:

    /* constructor */
//    #include "ENDFtk/section/28/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the number of subshells
     */
    int NSS() const { return this->subshells_.size(); }

    /**
     *  @brief Return the number of subshells
     */
    int numberSubshells() const { return this->NSS(); }

    /**
     *  @brief Return the subshell data data
     */
    auto reactionProducts() const {

      return ranges::cpp20::views::all( this->subshells_ );
    }

    #include "ENDFtk/section/28/src/NC.hpp"
    #include "ENDFtk/section/28/src/print.hpp"

    using Base::MT;
    using Base::sectionNumber;
    using Base::ZA;
    using Base::atomicWeightRatio;
    using Base::AWR;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
