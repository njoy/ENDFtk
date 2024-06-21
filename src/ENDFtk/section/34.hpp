#ifndef NJOY_ENDFTK_SECTION_34
#define NJOY_ENDFTK_SECTION_34

// system includes
#include <variant>

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/section/ExplicitCovariance.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief 34 - covariances for angular distributions
   *
   *  See ENDF102, section 34.2 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 34 > : protected Base {

  public:

    // include classes for subsections
    #include "ENDFtk/section/34/LegendreBlock.hpp"
    #include "ENDFtk/section/34/ReactionBlock.hpp"

  private:

    /* fields */
    int ltt_;
    std::vector< ReactionBlock > reactions_;

    /* auxiliary functions */

  public:

    /* constructor */
    #include "ENDFtk/section/34/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the representation of the covariances
     */
    int LTT() const { return this->ltt_; }

    /**
     *  @brief Return the representation of the covariances
     */
    int representation() const { return this->LTT(); }

    /**
     *  @brief Return the number of subsections
     */
    int NMT1() const { return this->reactions_.size(); }

    /**
     *  @brief Return the number of subsections, representing reactions
     */
    int numberReactions() const { return this->NMT1(); }

    /**
     *  @brief Return the subsections defined in this section
     */
    auto reactions() const {

      using namespace njoy::tools;
      return this->reactions_ | std20::views::all;
    }

    #include "ENDFtk/section/34/src/NC.hpp"
    #include "ENDFtk/section/34/src/print.hpp"

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
