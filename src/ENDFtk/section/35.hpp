#ifndef NJOY_ENDFTK_SECTION_35
#define NJOY_ENDFTK_SECTION_35

// system includes
#include <variant>

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief 35 - covariances for energy distributions
   *
   *  See ENDF102, section 35.2 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 35 > : protected Base {

  public:

    // include classes for subsections
    #include "ENDFtk/section/35/SquareMatrix.hpp"

  private:

    /* fields */
    std::vector< SquareMatrix > energyBlocks_;

    /* auxiliary functions */

  public:

    /* constructor */
    #include "ENDFtk/section/35/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the number of subsections
     */
    int NK() const { return this->energyBlocks_.size(); }

    /**
     *  @brief Return the number of subsections, representing energy blocks
     */
    int numberEnergyBlocks() const { return this->NK(); }

    /**
     *  @brief Return the subsections defined in this section
     */
    auto energyBlocks() const {

      using namespace njoy::tools;
      return this->energyBlocks_ | std20::views::all;
    }

    #include "ENDFtk/section/35/src/NC.hpp"
    #include "ENDFtk/section/35/src/print.hpp"

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
