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

    //! @todo pybind11 variant needs default constructor workaround
    #ifdef PYBIND11
    /**
     *  @brief Default constructor - only enabled for pybind11
     */
    Type() = default;
    #endif

    /**
     *  @brief Constructor
     *
     *  @param[in] mt             the MT number
     *  @param[in] zaid           the ZA  identifier
     *  @param[in] awr            the atomic mass ratio
     *  @param[in] qm             the mass difference Q value
     *  @param[in] qi             the reaction Q value
     *  @param[in] lr             the complex breakup flag
     *  @param[in] boundaries     the interpolation range boundaries
     *  @param[in] interpolants   the interpolation types for each range
     *  @param[in] energies       the energy values
     *  @param[in] xs             the cross section values
     */
    Type( int mt, int zaid, double awr, double qm, double qi, long lr,
          std::vector< long >&& boundaries, std::vector< long >&& interpolants,
          std::vector< double >&& energies, std::vector< double >&& xs ) :
      Base( zaid, awr, mt ),
      table( qm, qi, 0, lr,
             std::move( boundaries ), std::move( interpolants ),
             std::move( energies ), std::move( xs ) ) {}

    /**
     *  @brief Constructor for a single interpolation zone
     *
     *  @param[in] mt             the MT number
     *  @param[in] zaid           the ZA  identifier
     *  @param[in] awr            the atomic mass ratio
     *  @param[in] qm             the mass difference Q value
     *  @param[in] qi             the reaction Q value
     *  @param[in] energies       the energy values
     *  @param[in] xs             the cross section values
     *  @param[in] interpolant    the interpolation type (default 2 - linlin)
     *  @param[in] lr             the complex breakup flag (default 0)
     */
    Type( int mt, int zaid, double awr, double qm, double qi,
          std::vector< double >&& energies, std::vector< double >&& xs,
          long interpolant = 2, long lr = 0 ) :
      Type( mt, zaid, awr, qm, qi, lr,
            { static_cast<long>( energies.size() ) }, { interpolant },
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
      try: Base( head, MAT, 3 ),
           table( begin, end, lineNumber, head.MAT(), 3, head.MT() ){
        readSEND(begin, end, lineNumber, MAT, 3 );
      }
      catch( std::exception& e ) {

        Log::info
        ( "Encountered error while reading section {} of file 3 of material {}",
          head.MT(), MAT );
        throw e;
      }

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
