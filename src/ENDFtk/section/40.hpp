#ifndef NJOY_ENDFTK_SECTION_40
#define NJOY_ENDFTK_SECTION_40

// system includes
#include <variant>

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/section/ReactionBlock.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief 40 - covariances for radionuclide production
   *
   *  See ENDF102, section 40.2 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 40 > : protected Base {

  public:

    // include classes for subsections
    #include "ENDFtk/section/40/LevelBlock.hpp"

  private:

    /* fields */

    int lis_;
    std::vector< LevelBlock > levelBlocks_;

    /* auxiliary functions */

  public:

    /* constructor */

    /**
     *  @brief Constructor
     *
     *  @param[in] mt            the MT number of the section
     *  @param[in] zaid          the material ZAID value
     *  @param[in] awr           the atomic weight ratio
     *  @param[in] lis           the level number of target
     *  @param[in] blocks        the level block subsections
     */
    Type( int MT, int zaid, double awr, int lis,
          std::vector< LevelBlock >&& blocks ) :
      Base( zaid, awr, MT ), lis_( lis ),
      levelBlocks_( std::move( blocks ) ) {}

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
        Base( head, MAT, 40 ), lis_( head.L1() ),
        levelBlocks_(
          readSequence< LevelBlock >( begin, end, lineNumber,
                                      MAT, 40, head.MT(), head.N1() ) ) {
        readSEND(begin, end, lineNumber, MAT, 40 );
      } catch( std::exception& e ) {

        Log::info( "Trouble while reading section {} of File 40 of Material {}",
                   head.MT(), MAT );
        throw e;
      }

    /* methods */

    /**
     *  @brief Return the excited level number of the target
     */
    int LIS() const { return this->lis_; }

    /**
     *  @brief Return the excited level number of the target
     */
    int excitedLevel() const { return this->LIS(); }

    /**
     *  @brief Return the number of subsections
     */
    int NS() const { return this->levelBlocks_.size(); }

    /**
     *  @brief Return the number of subsections, representing levels
     */
    int numberLevelBlocks() const { return this->NS(); }

    /**
     *  @brief Return the subsections defined in this section
     */
    auto levelBlocks() const {

      using namespace njoy::tools;
      return std20::views::all( this->levelBlocks_ );
    }

    /**
     *  @brief Return the number of lines in this MF40 section
     */
    long NC() const {

      long NC = 1;
      for ( const auto& entry : this->levelBlocks_ ) { NC += entry.NC(); }
      return NC;
    };

    /**
     *  @brief Print the MF40 section (includes SEND record)
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
      ControlRecord( this->ZA(), this->AWR(), this->LIS(), 0,
                     this->NS(), 0 ).print( it, MAT, MF, MT );
      for ( const auto& entry : this->levelBlocks_ ) { entry.print( it, MAT, MF, MT ); }
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
