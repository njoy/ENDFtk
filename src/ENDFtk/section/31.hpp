#ifndef NJOY_ENDFTK_SECTION_31
#define NJOY_ENDFTK_SECTION_31

// system includes
#include <variant>

// other includes
#include "range/v3/range/conversion.hpp"
#include "range/v3/view/all.hpp"
#include "range/v3/view/concat.hpp"
#include "range/v3/view/drop_exactly.hpp"
#include "range/v3/view/take_exactly.hpp"
#include "range/v3/view/stride.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/section/ReactionBlock.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief 31 - covariances of fission multiplicities
   *
   *  See ENDF102, section 31.2 for more information.
   *
   *  Exactly the same as MF33, so most is taken from the 33 implementation.
   *  Caveat: lumped covariances don't make sense in MF31, so this is withheld.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 31 > : protected Base {

    /* fields */
    std::vector< ReactionBlock > reactions_;

    /* auxiliary functions */

  public:

    /* constructor */
    #include "ENDFtk/section/31/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the number of subsections
     */
    int NL() const { return this->reactions_.size(); }

    /**
     *  @brief Return the number of subsections, representing reactions
     */
    int numberReactions() const { return this->NL(); }

    /**
     *  @brief Return the subsections defined in this section
     */
    auto reactions() const {

      return ranges::cpp20::views::all( this->reactions_ );
    }

    #include "ENDFtk/section/31/src/NC.hpp"
    #include "ENDFtk/section/31/src/print.hpp"

    using Base::MT;
    using Base::sectionNumber;
    using Base::ZA;
    using Base::targetIdentifier;
    using Base::atomicWeightRatio;
    using Base::AWR;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
