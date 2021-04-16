#ifndef NJOY_ENDFTK_SECTION_8_459
#define NJOY_ENDFTK_SECTION_8_459

// system includes

// other includes
#include "range/v3/range/conversion.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/section/8/FissionYieldData.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  template<>
  class Type< 8, 459 > : protected BaseWithoutMT< Type< 8, 459 > > {

    friend BaseWithoutMT< Type< 8, 459 > >;

    /* fields */
    std::vector< FissionYieldData > data_;

    /* auxiliary functions */
    #include "ENDFtk/section/8/454/src/generateFissionYields.hpp" // taken from 454

  public:

    /* constructor */
    #include "ENDFtk/section/8/459/src/ctor.hpp"

    /* get methods */

    /**
     *  @brief Return whether or not the fission yields are energy dependent
     *         or not
     */
    bool LE() const { return this->data_.size() == 1; }

    /**
     *  @brief Return whether or not the fission yield data is energy independent
     */
    bool isEnergyIndependent() const { return this->LE(); }

    /**
     *  @brief Return the fission yield data, one for each incident energy
     */
    AllRange< FissionYieldData > yields() const {

      return ranges::cpp20::views::all( this->data_ );
    }

    /**
     *  @brief Return the number of incident energy values
     */
    long NE() const { return this->data_.size(); }

    /**
     *  @brief Return the incident energy values
     */
    auto E() const {

      return this->yields()
                 | ranges::cpp20::views::transform( [] ( const auto& entry )
                                                       { return entry.E(); } );
    }

    /**
    *  @brief Return the incident energy values
     */
    auto incidentEnergies() const { return this->E(); }

    #include "ENDFtk/section/8/459/src/NC.hpp"
    #include "ENDFtk/section/8/459/src/print.hpp"

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber() { return 459; }

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::atomicWeightRatio;
    using BaseWithoutMT::AWR;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
