#ifndef NJOY_ENDFTK_SECTION_9
#define NJOY_ENDFTK_SECTION_9

// system includes

// other includes
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief MF9 - multiplicities for radioactive nuclide production
   *
   *  See ENDF102, section 9.2 for more information.
   */
  template<>
  class Type< 9 > : protected Base {

  public:

    #include "ENDFtk/section/9/Multiplicity.hpp"

  private:

    /* fields */
    int lis_;
    std::vector< Multiplicity > states_;

  public:

    /* constructor */
    #include "ENDFtk/section/9/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the excited level number
     */
    int LIS() const { return this->lis_; }

    /**
     *  @brief Return the excited level number
     */
    int excitedLevel() const { return this->LIS(); }

    /**
     *  @brief Return the number of excited states for the reaction product
     */
    int NS() const { return this->states_.size(); }

    /**
     *  @brief Return the number of excited states for the reaction product
     */
    int numberExcitedStates() const { return this->NS(); }

    /**
     *  @brief Return the reaction product data
     */
    auto products() const {

      return ranges::view::all( this->states_ );
    }

    #include "ENDFtk/section/9/src/NC.hpp"
    #include "ENDFtk/section/9/src/print.hpp"

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
