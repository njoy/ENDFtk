#ifndef NJOY_ENDFTK_SECTION_32_151
#define NJOY_ENDFTK_SECTION_32_151

// system includes

// other includes
#include "range/v3/view/chunk.hpp"
#include "range/v3/view/drop_exactly.hpp"
#include "range/v3/view/stride.hpp"
#include "range/v3/view/transform.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/ListRecord.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF32 MT151 - resonance parameters
   *
   *  See ENDF102, section 32.1 for more information.
   */
  template<>
  class Type< 32, 151 > : protected BaseWithoutMT< Type< 32, 151 > > {

  public:

    #include "ENDFtk/section/32/151/BreitWignerLValue.hpp"

//    #include "ENDFtk/section/2/151/ScatteringRadius.hpp"
//    #include "ENDFtk/section/2/151/ResonanceRange.hpp"
//    #include "ENDFtk/section/2/151/Isotope.hpp"
//
  private:

    friend BaseWithoutMT< Type< 32, 151 > >;

//    /* fields */
//    std::vector< Isotope > isotopes_;
//
//    /* auxiliary functions */
//    #include "ENDFtk/section/2/151/src/verifyNIS.hpp"

  public:

    /* constructor */
    #include "ENDFtk/section/32/151/src/ctor.hpp"

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber() { return 151; }

//    /**
//     *  @brief Return the number NIS of isotopes
//     */
//    unsigned int numberIsotopes() const { return this->NIS(); }
//
//    /**
//     *  @brief Return the number NIS of isotopes
//     */
//    unsigned int NIS() const { return this->isotopes_.size(); }
//
//    /**
//     *  @brief Return the isotopes defined in the section
//     */
//    auto isotopes() const {
//
//      return ranges::cpp20::views::all( this->isotopes_ );
//    }
//
    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::atomicWeightRatio;
    using BaseWithoutMT::AWR;

    #include "ENDFtk/section/32/151/src/print.hpp"
    #include "ENDFtk/section/32/151/src/NC.hpp"
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
