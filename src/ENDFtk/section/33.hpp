#ifndef NJOY_ENDFTK_SECTION_33
#define NJOY_ENDFTK_SECTION_33

// system includes
#include <variant>

// other includes
#include "range/v3/range/conversion.hpp"
#include "range/v3/view/all.hpp"
#include "range/v3/view/concat.hpp"
#include "range/v3/view/drop_exactly.hpp"
#include "range/v3/view/take_exactly.hpp"
#include "range/v3/view/stride.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/section/covariance.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief 33 - covariances of cross sections
   *
   *  See ENDF102, section 33.2 for more information.
   */
  template<>
  class Type< 33 > : protected Base {

    /* fields */
    int mtl_;
    std::vector< ReactionBlock > reactions_;

    /* auxiliary functions */

  public:

    /* constructor */
    #include "ENDFtk/section/33/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the lumped covariance index
     */
    int MTL() const { return this->mtl_; }

    /**
     *  @brief Return the lumped covariance index
     */
    int lumpedCovarianceIndex() const { return this->MTL(); }

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

    #include "ENDFtk/section/33/src/NC.hpp"
    #include "ENDFtk/section/33/src/print.hpp"

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
