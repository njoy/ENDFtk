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
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief 31 - covariances of cross sections
   *
   *  See ENDF102, section 31.2 for more information.
   *
   *  Exactly the same as MF33, so most is taken from the 33 implementation.
   *  Caveat: lumped covariances don't make sense in MF31, so this is witheld.
   */
  template<>
  class Type< 31 > : protected Base {

  public:

    // all includes intentionally taken from MF33

    // include classes for subsubsections
    #include "ENDFtk/section/33/DerivedRedundant.hpp"
    #include "ENDFtk/section/33/DerivedRatioToStandard.hpp"
    using DerivedCovariance = std::variant<
      DerivedRedundant,
      DerivedRatioToStandard >;

    #include "ENDFtk/section/33/CovariancePairs.hpp"
    #include "ENDFtk/section/33/SquareMatrix.hpp"
    #include "ENDFtk/section/33/RectangularMatrix.hpp"
    using ExplicitCovariance = std::variant<
      CovariancePairs,
      SquareMatrix,
      RectangularMatrix >;

    // include classes for subsections
    #include "ENDFtk/section/33/ReactionBlock.hpp"


  private:

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
    using Base::atomicWeightRatio;
    using Base::AWR;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
