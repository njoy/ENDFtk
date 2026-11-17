#ifndef NJOY_ENDFTK_SECTION_5
#define NJOY_ENDFTK_SECTION_5

// system includes
#include <variant>
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
  class ENDFTK_PYTHON_EXPORT Type< 5 > : protected Base {

  public:

    #include "ENDFtk/section/5/DistributionFunction.hpp"
    #include "ENDFtk/section/5/Parameter.hpp"
    #include "ENDFtk/section/5/EffectiveTemperature.hpp"

    #include "ENDFtk/section/5/TabulatedSpectrum.hpp"            // LF=1
    #include "ENDFtk/section/5/GeneralEvaporationSpectrum.hpp"   // LF=5
    #include "ENDFtk/section/5/MaxwellianFissionSpectrum.hpp"    // LF=7
    #include "ENDFtk/section/5/EvaporationSpectrum.hpp"          // LF=9
    #include "ENDFtk/section/5/WattSpectrum.hpp"                 // LF=11
    #include "ENDFtk/section/5/MadlandNixSpectrum.hpp"           // LF=12

    using LF1 = TabulatedSpectrum;
    using LF5 = GeneralEvaporationSpectrum;
    using LF7 = MaxwellianFissionSpectrum;
    using LF9 = EvaporationSpectrum;
    using LF11 = WattSpectrum;
    using LF12 = MadlandNixSpectrum;

    /** @typedef Distribution
     *  @brief A secondary particle energy distribution of MF5
     */
    using Distribution = std::variant< TabulatedSpectrum,           // LF=1
                                       GeneralEvaporationSpectrum,  // LF=5
                                       MaxwellianFissionSpectrum,   // LF=7
                                       EvaporationSpectrum,         // LF=9
                                       WattSpectrum,                // LF=11
                                       MadlandNixSpectrum >;        // LF=12
    #include "ENDFtk/section/5/Probability.hpp"

    #include "ENDFtk/section/5/PartialDistribution.hpp"

  private:

    /* fields */

    std::vector< PartialDistribution > partials_;

    /* auxiliary functions */

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
        Base( head, MAT, 5 ),
        partials_( readSequence< PartialDistribution >(
                       begin, end, lineNumber,
                       MAT, 5, head.MT(), head.N1() ) ) {
        verifyNK( this->NK() );
        readSEND( begin, end, lineNumber, MAT, 5 );
      } catch( std::exception& e ) {
        Log::info( "Trouble while reading section {} of File 5 of Material {}",
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

    /**
     *  @brief Return the number of lines in this MF5 section
     */
    long NC() const {

      long NC = 1;
      for ( const auto& entry : this->partials_ ) { NC += entry.NC(); }
      return NC;
    };

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
