#ifndef NJOY_ENDFTK_SECTION_23
#define NJOY_ENDFTK_SECTION_23

// system includes

// other includes
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF23 - smooth photon interaction cross sections
   *
   *  See ENDF102, section 23.3 for more information.
   */
  template<>
  class Type< 23 > : protected Base {

    /* fields */
    TabulationRecord table;

  public:

    /* constructor */
    #include "ENDFtk/section/23/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the subshell binding energy
     */
    double EPE() const { return this->table.C1(); }

    /**
     *  @brief Return the subshell binding energy
     */
    double subshellBindingEnergy() const { return this->EPE(); }

    /**
     *  @brief Return the fluorescence yield (eV/photoionisation)
     */
    double EFL() const { return this->table.C2(); }

    /**
     *  @brief Return the fluorescence yield (eV/photoionisation)
     */
    double fluorescenceYield() const { return this->EFL(); }

    /**
     *  @brief Return the number of interpolation ranges
     */
    long NR() const { return this->table.NR(); }

    /**
     *  @brief Return the number of points
     */
    long NP() const { return this->table.NP(); }

    /**
     *  @brief Return the interpolation type for each range
     */
    auto interpolants() const { return this->table.interpolants(); }

    /**
     *  @brief Return the interpolation boundaries
     */
    auto boundaries() const { return this->table.boundaries(); }

    /**
     *  @brief Return the energy values
     */
    auto energies() const { return this->table.x(); }

    /**
     *  @brief Return the cross section values
     */
    auto crossSections() const { return this->table.y(); }

    /**
     *  @brief Return the number of lines in this MF23 section
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

    /**
     *  @brief Return the interpolation regions (common interface for
     *         interpolation tables)
     */
    auto regions() const { return this->table.regions(); }

    #include "ENDFtk/section/3/src/print.hpp"  // taken from MF3

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
