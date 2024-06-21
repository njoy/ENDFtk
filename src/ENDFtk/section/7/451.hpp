#ifndef NJOY_ENDFTK_SECTION_7_451
#define NJOY_ENDFTK_SECTION_7_451

// system includes
#include <vector>

// other includes
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/readSequence.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  template<>
  class ENDFTK_PYTHON_EXPORT Type< 7, 451 > :
    protected BaseWithoutMT< Type< 7, 451 > > {

    friend BaseWithoutMT< Type< 7, 451 > >;

  public:

    #include "ENDFtk/section/7/451/ElementInformation.hpp"

  private:

    /* fields */
    std::vector< ElementInformation > elements_;

    /* auxiliary functions */
    #include "ENDFtk/section/7/451/src/verifySize.hpp"

  public:

    /* constructor */
    #include "ENDFtk/section/7/451/src/ctor.hpp"

    /* get methods */

    /**
     *  @brief Return the number of elements
     */
    unsigned int NA() const { return this->elements_.size(); }

    /**
     *  @brief Return the number of elements
     */
    unsigned int numberElements() const { return this->NA(); }

    /**
     *  @brief Return the element data
     */
    auto elements() const {

      return ranges::cpp20::views::all( this->elements_ );
    }

    #include "ENDFtk/section/7/451/src/NC.hpp"
    #include "ENDFtk/section/7/451/src/print.hpp"

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber() { return 451; }

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::targetIdentifier;
    using BaseWithoutMT::AWR;
    using BaseWithoutMT::atomicWeightRatio;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
