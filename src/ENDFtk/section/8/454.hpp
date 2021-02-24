#ifndef NJOY_ENDFTK_SECTION_8_454
#define NJOY_ENDFTK_SECTION_8_454

// system includes

// other includes
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/section/8/FissionYieldData.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  template<>
  class Type< 8, 454 > : protected BaseWithoutMT< Type< 8, 454 > > {

    friend BaseWithoutMT< Type< 8, 454 > >;

    /* fields */
    std::vector< FissionYieldData > data_;

    /* auxiliary functions */
    #include "ENDFtk/section/8/454/src/generateFissionYields.hpp"

  public:

    /* constructor */
    #include "ENDFtk/section/8/454/src/ctor.hpp"

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
     *  @brief Return the subsections, one for each incident energy
     */
    auto yields() const { return ranges::view::all( this->data_ ); }

    /**
     *  @brief Return the incident energy values
     */
    auto E() const {

      return this->yields()
                 | ranges::view::transform( [] ( const auto& entry )
                                               { return entry.E(); } );
    }

    /**
    *  @brief Return the incident energy values
     */
    auto incidentEnergies() const { return this->E(); }

    #include "ENDFtk/section/8/454/src/NC.hpp"
    #include "ENDFtk/section/8/454/src/print.hpp"

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber() { return 454; }

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::atomicWeightRatio;
    using BaseWithoutMT::AWR;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
