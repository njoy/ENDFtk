#ifndef NJOY_ENDFTK_SECTION_35
#define NJOY_ENDFTK_SECTION_35

// system includes
#include <variant>

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief 35 - covariances for energy distributions
   *
   *  See ENDF102, section 35.2 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 35 > : protected Base {

  public:

    // include classes for subsections
    #include "ENDFtk/section/35/SquareMatrix.hpp"

  private:

    /* fields */

    std::vector< SquareMatrix > energyBlocks_;

    /* auxiliary functions */

  public:

    /* constructor */

    /**
     *  @brief Constructor
     *
     *  @param[in] mt            the MT number of the section
     *  @param[in] zaid          the material ZAID value
     *  @param[in] awr           the atomic weight ratio
     *  @param[in] blocks        the energy block subsections
     */
    Type( int MT, int zaid, double awr,
          std::vector< SquareMatrix >&& blocks ) :
      Base( zaid, awr, MT ),
      energyBlocks_( std::move( blocks ) ) {}

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
    Type( HEAD& head,
          Iterator& begin,
          const Iterator& end,
          long& lineNumber,
          int MAT )
      try:
        Base( head, MAT, 35 ),
        energyBlocks_(
          readSequence< SquareMatrix >( begin, end, lineNumber,
                                        MAT, 35, head.MT(), head.N1() ) ) {

        readSEND(begin, end, lineNumber, MAT, 35 );
      } catch( std::exception& e ) {

        Log::info( "Trouble while reading section {} of File 35 of Material {}",
                   head.MT(), MAT );
        throw e;
      }

    /* methods */

    /**
     *  @brief Return the number of subsections
     */
    int NK() const { return this->energyBlocks_.size(); }

    /**
     *  @brief Return the number of subsections, representing energy blocks
     */
    int numberEnergyBlocks() const { return this->NK(); }

    /**
     *  @brief Return the subsections defined in this section
     */
    auto energyBlocks() const {

      using namespace njoy::tools;
      return std20::views::all( this->energyBlocks_ );
    }

    /**
     *  @brief Return the number of lines in this MF35 section
     */
    long NC() const {

      long NC = 1;
      for ( const auto& entry : this->energyBlocks_ ) { NC += entry.NC(); }
      return NC;
    };

    /**
     *  @brief Print the MF35 section (includes SEND record)
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
      ControlRecord( this->ZA(), this->AWR(), 0, 0,
                     this->NK(), 0 ).print( it, MAT, MF, MT );
      for ( const auto& entry : this->energyBlocks_ ) { entry.print( it, MAT, MF, MT ); }
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
