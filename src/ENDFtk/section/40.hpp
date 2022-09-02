#ifndef NJOY_ENDFTK_SECTION_40
#define NJOY_ENDFTK_SECTION_40

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
   *  @brief 40 - covariances for radionuclide production
   *
   *  See ENDF102, section 40.2 for more information.
   */
  template<>
  class Type< 40 > : protected Base {

  public:

    // include classes for subsubsubsections
    // taken from MF33 intentionally
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

    // include classes for subsubsections
    // taken from MF33 intentionally
    #include "ENDFtk/section/33/ReactionBlock.hpp"

    // include classes for subsections
    #include "ENDFtk/section/40/LevelBlock.hpp"

  private:

    /* fields */
    int lis_;
    std::vector< LevelBlock > levelBlocks_;

    /* auxiliary functions */

  public:

    /* constructor */
    #include "ENDFtk/section/40/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the excited level number of the target
     */
    int LIS() const { return this->lis_; }

    /**
     *  @brief Return the excited level number of the target
     */
    int excitedLevel() const { return this->LIS(); }

    /**
     *  @brief Return the number of subsections
     */
    int NS() const { return this->levelBlocks_.size(); }

    /**
     *  @brief Return the number of subsections, representing levels
     */
    int numberLevelBlocks() const { return this->NS(); }

    /**
     *  @brief Return the subsections defined in this section
     */
    auto levelBlocks() const {

      return ranges::cpp20::views::all( this->levelBlocks_ );
    }

    #include "ENDFtk/section/40/src/NC.hpp"
    #include "ENDFtk/section/40/src/print.hpp"

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
