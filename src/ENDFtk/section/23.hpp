#ifndef NJOY_ENDFTK_SECTION_23
#define NJOY_ENDFTK_SECTION_23

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
   *  @brief MF23 - smooth photon interaction cross sections
   *
   *  See ENDF102, section 23.3 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 23 > : protected Base {

    /* fields */

    TabulationRecord table;

  public:

    /* constructor */

    /**
     *  @brief Constructor
     *
     *  @param[in] mt             the MT number
     *  @param[in] zaid           the ZA  identifier
     *  @param[in] awr            the atomic mass ratio
     *  @param[in] epe            the subshell binding energy
     *  @param[in] efl            the fluorescence yield
     *  @param[in] boundaries     the interpolation range boundaries
     *  @param[in] interpolants   the interpolation types for each range
     *  @param[in] energies       the energy values
     *  @param[in] xs             the cross section values
     */
    Type( int mt, int zaid, double awr, double epe, double efl, 
          std::vector< long >&& boundaries, std::vector< long >&& interpolants,
          std::vector< double >&& energies, std::vector< double >&& xs ) :
      Base( zaid, awr, mt ),
      table( epe, efl, 0, 0,
             std::move( boundaries ), std::move( interpolants ),
             std::move( energies ), std::move( xs ) ) {}

    /**
     *  @brief Constructor (from a buffer)
     *
     *  @tparam Iterator        a buffer iterator
     *
     *  @param[in] head         the head record of the section
     *  @param[in] it           the current position in the buffer
     *  @param[in] end          the end of the buffer
     *  @param[in] lineNumber   the current line number
     *  @param[in] MAT          the expected MAT number
     */
    template< typename Iterator >
    Type ( HEAD& head,
           Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT )
      try: Base( head, MAT, 23 ),
           table( begin, end, lineNumber, head.MAT(), 23, head.MT() ){
        readSEND(begin, end, lineNumber, MAT, 23 );
      }
      catch( std::exception& e ) {

        Log::info
        ( "Encountered error while reading section {} of file 23 of material {}",
          head.MT(), MAT );
        throw e;
      }

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
     *  @brief Return the interpolation type for each region
     */
    auto INT() const { return this->table.interpolants(); }

    /**
     *  @brief Return the interpolation type for each region
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

    // taken from MF3

    /**
     *  @brief Print the MF3 section (includes SEND record)
     *
     *  @tparam OutputIterator   an output iterator
     *
     *  @param[in] it            the current position in the output
     *  @param[in] MAT           the MAT number
     *  @param[in] MF            the MF number
     */
    template< typename OutputIterator >
    void print( OutputIterator& it, int MAT, int MF ) const {

      int MT = this->MT();
      ControlRecord( this->ZA(), this->AWR(), 0, 0, 0, 0 ).print( it, MAT, MF, MT );
      this->table.print( it, MAT, MF, MT );
      SEND( MAT, MF ).print( it );
    }

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
