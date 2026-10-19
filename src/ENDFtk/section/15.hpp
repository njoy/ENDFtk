#ifndef NJOY_ENDFTK_SECTION_15
#define NJOY_ENDFTK_SECTION_15

// system includes
#include <vector>

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/InterpolationSequenceRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  template<>
  class ENDFTK_PYTHON_EXPORT Type< 15 > : protected Base {

  public:

    #include "ENDFtk/section/5/TabulatedSpectrum.hpp"    // LF=1, taken from MF5

    using LF1 = TabulatedSpectrum;

    /** @typedef Distribution
     *  @brief A secondary particle energy distribution of MF15
     */
    using Distribution = TabulatedSpectrum; // LF=1

    #include "ENDFtk/section/5/Probability.hpp"          // taken from MF5
    #include "ENDFtk/section/15/PartialDistribution.hpp"

  private:

    /* fields */

    std::vector< PartialDistribution > partials_;

    /* auxiliary functions */

    // taken from MF5

    static void
    verifyNK( int NK ) {

      if ( NK == 0 ) {

        Log::error( "No partial distributions were defined" );
        Log::info( "NK must be non zero" );
        throw std::exception();
      }
    }

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
     *  @param[in] mt            the MT number of the section
     *  @param[in] zaid          the material ZAID value
     *  @param[in] awr           the atomic weight ratio
     *  @param[in] partials      the partial distributions (at least 1)
     */
    Type( int mt, int zaid, double awr,
          std::vector< PartialDistribution >&& partials ) :
      Base( zaid, awr, mt ), partials_( std::move( partials ) ) {

      verifyNK( this->NK() );
    }

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
        Base( head, MAT, 15 ),
        partials_( readSequence< PartialDistribution >(
                       begin, end, lineNumber,
                       MAT, 15, head.MT(), head.N1() ) ) {
        verifyNK( this->NK() );
        readSEND( begin, end, lineNumber, MAT, 15 );
      } catch( std::exception& e ) {
        Log::info( "Trouble while reading section {} of File 15 of Material {}",
                   head.MT(), MAT );
        throw e;
      }

    /* methods */

    /**
     *  @brief Return the number NK of subsections with partial distributions
     */
    int NK() const { return this->partials_.size(); }

    /**
     *  @brief Return the number NK of subsections with partial distributions
     */
    int numberPartialDistributions() const { return this->NK(); }

    /**
     *  @brief Return the partial distributions defined in this section
     */
    auto partialDistributions() const {

      using namespace njoy::tools;
      return std20::views::all( this->partials_ );
    }

    // taken from MF5

    /**
     *  @brief Return the number of lines in this MF5 section
     */
    long NC() const {

      long NC = 1;
      for ( const auto& entry : this->partials_ ) { NC += entry.NC(); }
      return NC;
    };

    // taken from MF5

    /**
     *  @brief Print the MF5 section (includes SEND record)
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
      for ( auto& entry : this->partials_ ) { entry.print( it, MAT, MF, MT ); }
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
