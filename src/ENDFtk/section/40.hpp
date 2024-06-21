#ifndef NJOY_ENDFTK_SECTION_40
#define NJOY_ENDFTK_SECTION_40

// system includes
#include <variant>

// other includes
#include "tools/std20/views.hpp"
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
   *  @brief 40 - covariances for radionuclide production
   *
   *  See ENDF102, section 40.2 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 40 > : protected Base {

  public:

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

      using namespace njoy::tools;
      return this->levelBlocks_ | std20::views::all;
    }

    #include "ENDFtk/section/40/src/NC.hpp"
    #include "ENDFtk/section/40/src/print.hpp"

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
