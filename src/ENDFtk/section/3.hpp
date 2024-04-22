#ifndef NJOY_ENDFTK_SECTION_3
#define NJOY_ENDFTK_SECTION_3

// system includes

// other includes
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF3 - reaction cross sections
   *
   *  See ENDF102, section 3.2 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 3 > : protected Base {

    /* fields */
    TabulationRecord table;

  public:

    /* constructor */
    #include "ENDFtk/section/3/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the mass difference Q value
     */
    double QM() const { return this->table.C1(); }

    /**
     *  @brief Return the mass difference Q value
     */
    double massDifferenceQValue() const { return this->QM(); }

    /**
     *  @brief Return the reaction Q value
     */
    double QI() const { return this->table.C2(); }

    /**
     *  @brief Return the reaction Q value
     */
    double reactionQValue() const { return this->QI(); }

    /**
     *  @brief Return the complex break up flag
     */
    int LR() const { return this->table.L2(); }

    /**
     *  @brief Return the complex break up flag
     */
    int complexBreakUp() const { return this->LR(); }

    /**
     *  @brief Return the number of interpolation ranges
     */
    long NR() const { return this->table.NR(); }

    /**
     *  @brief Return the number of points
     */
    long numberInterpolationRegions() const {

      return this->table.numberInterpolationRegions();
    }

    /**
     *  @brief Return the number of points
     */
    long NP() const { return this->table.NP(); }

    /**
     *  @brief Return the number of points
     */
    long numberPoints() const { return this->NP(); }

    /**
     *  @brief Return the interpolation type for each range
     */
    auto INT() const { return this->table.INT(); }

    /**
     *  @brief Return the interpolation type for each range
     */
    auto interpolants() const { return this->INT(); }

    /**
     *  @brief Return the interpolation boundaries
     */
    auto NBT() const { return this->table.NBT(); }

    /**
     *  @brief Return the interpolation boundaries
     */
    auto boundaries() const { return this->NBT(); }

    /**
     *  @brief Return the energy values
     */
    auto energies() const { return this->table.x(); }

    /**
     *  @brief Return the cross section values
     */
    auto crossSections() const { return this->table.y(); }

    /**
     *  @brief Return the number of lines in this MF3 section
     */
    long NC() const { return this->table.NC() + 1; }

    /**
     *  @brief Return the energy values (common interface for interpolation
     *         tables)
     */
    auto x() const { return this->energies(); }

    /**
     *  @brief Return the cross section values (common interface for interpolation
     *         tables)
     */
    auto y() const { return this->crossSections(); }

    #include "ENDFtk/section/3/src/print.hpp"

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
