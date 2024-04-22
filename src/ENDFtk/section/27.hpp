#ifndef NJOY_ENDFTK_SECTION_27
#define NJOY_ENDFTK_SECTION_27

// system includes

// other includes
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief MF27 - atomic form factors or scattering functions
   *
   *  See ENDF102, section 27.2 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 27 > : protected Base {

    /* fields */
    TabulationRecord table;

  public:

    /* constructor */
    #include "ENDFtk/section/27/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the Z number of the atom
     */
    unsigned int Z() const { return this->table.C2(); }

    /**
     *  @brief Return the Z number of the atom
     */
    unsigned int atomZ() const { return this->Z(); }

    /**
     *  @brief Return the number of interpolation regions
     */
    long NR() const { return this->table.NR(); }

    /**
     *  @brief Return the number of interpolation regions
     */
    long numberInterpolationRegions() const { return this->NR(); }

    /**
     *  @brief Return the number of points
     */
    long NP() const { return this->table.NP(); }

    /**
     *  @brief Return the number of points
     */
    long numberPoints() const { return this->NP(); }

    /**
     *  @brief Return the interpolation type for each regions
     */
    auto INT() const { return this->table.interpolants(); }

    /**
     *  @brief Return the interpolation type for each regions
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
     *  @brief Return the x values
     */
    auto X() const { return this->table.x(); }

    /**
     *  @brief Return the form factor or scattering function values
     */
    auto H() const { return this->table.y(); }

    /**
     *  @brief Return the form factor or scattering function values
     */
    long NC() const { return this->table.NC() + 1; }

    /**
     *  @brief Return the energy values (common interface for interpolation
     *         tables)
     */
    auto x() const { return this->X(); }

    /**
     *  @brief Return the values (common interface for interpolation
     *         tables)
     */
    auto y() const { return this->H(); }

    #include "ENDFtk/section/3/src/print.hpp" // taken from MF3

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
