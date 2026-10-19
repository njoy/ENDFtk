#ifndef NJOY_ENDFTK_SECTION_7_4
#define NJOY_ENDFTK_SECTION_7_4

// system includes
#include <variant>
#include <optional>
#include <vector>
#include <optional>

// other includes
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/InterpolationSequenceRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  template<>
  class ENDFTK_PYTHON_EXPORT Type< 7, 4 > :
    protected BaseWithoutMT< Type< 7, 4 > > {

    friend BaseWithoutMT< Type< 7, 4 > >;

  public:

    #include "ENDFtk/section/7/4/ScatteringLawConstants.hpp"

    #include "ENDFtk/section/7/4/AnalyticalFunctions.hpp"
    #include "ENDFtk/section/7/4/TabulatedFunctions.hpp"

    #include "ENDFtk/section/7/4/EffectiveTemperature.hpp"

    /** @typedef ScatteringLaw
     *  @brief The incoherent inelastic scattering law of MF7/MT4
     *
     *  This scattering law class is set up as a variant because the incoherent
     *  inelastic scattering law in MF7/MT4 can either be a given as analytical
     *  functions or as a tabulated S(a,b) function.
     */
    using ScatteringLaw = std::variant< // B(1)=0
                                        AnalyticalFunctions,
                                        // B(1)!=0
                                        TabulatedFunctions >;

    /* type aliases */

    using OptionalEffectiveTemperature = std::optional< EffectiveTemperature >;

  private:

    /* fields */

    int lat_;
    int lasym_;

    ScatteringLawConstants b_;
    ScatteringLaw law_;

    EffectiveTemperature principal_;
    std::vector< OptionalEffectiveTemperature > secondary_;

    /* auxiliary functions */

    template< typename Iterator, typename Array >
    static std::vector< std::optional< EffectiveTemperature > >
    readSecondaryTemperatures( Iterator& begin,
                               const Iterator& end,
                               long& lineNumber,
                               int MAT,
                               int MF,
                               int MT,
                               const Array& types ) {
      unsigned int size = types.size();
      std::vector< std::optional< EffectiveTemperature > > sequence;
      sequence.reserve( size );

      while( size-- ){
        if ( types[ sequence.size() ] == 0 ) {
          sequence.push_back( EffectiveTemperature( begin, end, lineNumber,
                                                    MAT, MF, MT ) );
        }
        else {
          sequence.push_back( std::nullopt );
        }
      }

      return sequence;
    }

    template< typename Iterator >
    static ScatteringLaw
    readScatteringLaw( Iterator& begin,
                       const Iterator& end,
                       long& lineNumber,
                       int MAT,
                       int MF,
                       int MT,
                       double B1 ) {

      if ( B1 == 0.0 ) {

        return AnalyticalFunctions();
      }
      else {

        return TabulatedFunctions( begin, end, lineNumber, MAT, MF, MT );
      }
    }

    static void
    checkValue( int value, const std::string& name ) {

      if ( ( value != 0 ) and ( value != 1 ) ) {

        Log::error( "Encountered illegal {} value", name );
        Log::info( "{} must be equal to 0 or 1", name );
        Log::info( "{} value: {}", name, value );
        throw std::exception();
      }
    }

    template< typename TypeArray, typename TemperatureArray >
    static void
    verifySecondaryTemperatures( const TypeArray& types,
                                 const TemperatureArray& temperatures ) {

      if ( types.size() != temperatures.size() ) {

        Log::error( "The data in the scattering constants and the number of "
                    "provided secondary effective temperatures are inconsistent" );
        Log::info( "Expected: {} optional temperature functions", types.size() );
        Log::info( "Found: {} optional temperature functions",
                   temperatures.size() );
        throw std::exception();
      }

      if ( types.size() > 0 ) {

        using namespace njoy::tools;
        auto needTemperature = types | std20::views::transform( [] ( double value )
                                                                   { return value == 0.0; } );

        auto haveTemperature = temperatures | std20::views::transform( [] ( auto&& value )
                                                                          { return bool( value ); } );

        std::vector< bool > verify;
        std::transform( needTemperature.begin(), needTemperature.end(), haveTemperature.begin(),
                        std::back_inserter( verify ), std::equal_to<>{} );

        auto iter = std20::find( verify, false );

        if ( iter != verify.end() ) {

          Log::error( "Available effective temperature data for secondary "
                      "scatterers inconsistent with the thermal scattering "
                      "constants data" );
          Log::info( "When B(7), B(13) or B(19) is zero, an effective temperature "
                     "must be given" );
          Log::info( "Encountered issue for the secondary scatterer with index={}",
                     std20::distance( std20::begin( verify ), iter ) );
          throw std::exception();
        }
      }
    }

    /* constructor */

    /**
     *  @brief Private intermediate constructor
     */
    template< typename Iterator >
    Type( int zaid, double awr, int lat, int lasym,
          ScatteringLawConstants&& constants,
          ScatteringLaw&& law,
          EffectiveTemperature&& principals,
          Iterator& begin,
          const Iterator& end,
          long& lineNumber,
          int MAT,
          int MF,
          int MT ) :
      Type( zaid, awr, lat, lasym,
            std::move( constants ),
            std::move( law ),
            std::move( principals ),
            readSecondaryTemperatures( begin, end, lineNumber,MAT, MF, MT,
                                       constants.analyticalFunctionTypes() ) ) {}

    /**
     *  @brief Private intermediate constructor
     */
    template< typename Iterator >
    Type( int zaid, double awr, int lat, int lasym,
          ScatteringLawConstants&& constants,
          ScatteringLaw&& law,
          Iterator& begin,
          const Iterator& end,
          long& lineNumber,
          int MAT,
          int MF,
          int MT ) :
      Type( zaid, awr, lat, lasym,
            std::move( constants ),
            std::move( law ),
            EffectiveTemperature( begin, end, lineNumber, MAT, MF, MT ),
            begin, end, lineNumber, MAT, MF, MT ) {}

    /**
     *  @brief Private intermediate constructor
     */
    template< typename Iterator >
    Type( int zaid, double awr, int lat, int lasym,
          ScatteringLawConstants&& constants,
          Iterator& begin,
          const Iterator& end,
          long& lineNumber,
          int MAT,
          int MF,
          int MT ) :
      Type( zaid, awr, lat, lasym,
            std::move( constants ),
            readScatteringLaw( begin, end, lineNumber, MAT, MF, MT,
                               constants.totalFreeCrossSections()[0] ),
            begin, end, lineNumber, MAT, MF, MT ) {}

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
     *  @param[in] zaid          the material ZAID value
     *  @param[in] awr           the atomic weight ratio
     *  @param[in] lat           the temperature flag for alpha and
     *                           beta grid
     *  @param[in] lasym         the S(a,b) symmetry flag
     *  @param[in] constants     the thermal scattering law constants
     *  @param[in] law           the thermal scattering law
     *  @param[in] principals    the effective temperature of the
     *                                     principal scatterer
     *  @param[in] secondaries   the effective temperature of the
     *                           secondary scatterers (if required)
     */
    Type( int zaid, double awr, int lat, int lasym,
          ScatteringLawConstants&& constants,
          ScatteringLaw&& law,
          EffectiveTemperature&& principal,
          std::vector< std::optional< EffectiveTemperature > >
              secondaries = {} ) :
      BaseWithoutMT( zaid, awr ), lat_( lat ), lasym_( lasym ),
      b_( std::move( constants ) ), law_( std::move( law ) ),
      principal_( std::move( principal ) ),
      secondary_( std::move( secondaries ) ) {

      verifySecondaryTemperatures( this->b_.analyticalFunctionTypes(),
                                   this->secondary_ );
      checkValue( this->LAT(), "LAT" );
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
      try : Type( head.ZA(), head.AWR(), head.L2(), head.N1(),
                  ScatteringLawConstants( begin, end, lineNumber, MAT, 7, 4 ),
                  begin, end, lineNumber, MAT, 7, 4 ) {
        readSEND(begin, end, lineNumber, MAT, 7 );
      } catch ( std::exception& e ) {
        Log::info( "Trouble while reading section 4 of File 7 of Material {}",
                   MAT );
        throw e;
      }

    /* get methods */

    /**
     *  @brief Return the LAT flag (temperature flag for alpha and beta grid)
     */
    int LAT() const { return this->lat_; }

    /**
     *  @brief Return the LAT flag (temperature flag for alpha and beta grid)
     */
    int temperatureOption() const { return this->LAT(); }

    /**
     *  @brief Return the LASYM flag (S(alpha,beta) is symmetric or not)
     */
    int LASYM() const { return this->lasym_; }

    /**
     *  @brief Return the LASYM flag (S(alpha,beta) is symmetric or not)
     */
    int symmetryOption() const { return this->LASYM(); }

    /**
     *  @brief Return the thermal scattering law constants for the principal and
     *         and secondary scatterers (if any)
     */
    const ScatteringLawConstants& constants() const { return this->b_; }

    /**
     *  @brief Return the thermal scattering law (either analytical or tabulated)
     */
    const ScatteringLaw& scatteringLaw() const { return this->law_; }

    /**
     *  @brief Return the effective temperature for the principal scatterer
     */
    const EffectiveTemperature& principalEffectiveTemperature() const {

      return this->principal_;
    }

    /**
     *  @brief Return the effective temperatures for the secondary scatterers
     *         (if any are defined)
     */
    auto secondaryEffectiveTemperatures() const {

      using namespace njoy::tools;
      return std20::views::all( this->secondary_ );
    }

    /** 
     *  @brief Return the number of lines in this MF7/MT4 section
     */
    long NC() const {
      long NC = 1 + this->b_.NC()
              + std::visit( [&] ( const auto& v ) { return v.NC(); }, this->law_ )
              + principal_.NC();
      for ( const auto& entry : this->secondary_ ) {

        if ( entry ) NC += entry->NC();
      }
      return NC;
    };

    /** 
     *  @brief Print the MF7/MT4 section (includes SEND record)
     *
     *  @tparam OutputIterator   an output iterator
     *
     *  @param[in] it            the current position in the output
     *  @param[in] MAT           the MAT number
     *  @param[in] MF            the MF number
     */
    template< typename OutputIterator >
    void print( OutputIterator& it, int MAT, int MF ) const {
      int MT = 4;
      ControlRecord( this->ZA(), this->AWR(), 0, this->LAT(),
                     this->LASYM(), 0 ).print( it, MAT, MF, MT );
      this->b_.print( it, MAT, MF, MT );
      std::visit( [&] ( const auto& v ) -> void
                      { v.print( it, MAT, MF, MT ); },
                  this->law_ );
      this->principal_.print( it, MAT, MF, MT );
      for ( const auto& entry : this->secondary_ ) {
        if ( entry ) entry->print( it, MAT, MF, MT );
      }
      SEND( MAT, MF ).print( it );
    } 

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber() { return 4; }

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::targetIdentifier;
    using BaseWithoutMT::AWR;
    using BaseWithoutMT::atomicWeightRatio;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
