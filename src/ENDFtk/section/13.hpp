#ifndef NJOY_ENDFTK_SECTION_13
#define NJOY_ENDFTK_SECTION_13

// system includes
#include <vector>
#include <optional>

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF13 - photon production cross sections
   *
   *  See ENDF102, section 13.2 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 13 > : protected Base {

  public:

    #include "ENDFtk/section/13/TotalCrossSection.hpp"
    #include "ENDFtk/section/13/PartialCrossSection.hpp"

    using OptionalTotalCrossSection = std::optional< TotalCrossSection >;

  private:

    /* fields */

    OptionalTotalCrossSection total_;
    std::vector< PartialCrossSection > partials_;

    /* auxiliary functions */

    static void
    verifyNK( int NK ) {

      if ( NK <= 0 ) {

        Log::error( "Encountered illegal NK value" );
        Log::info( "NK must be larger than 0" );
        Log::info( "NK value: {}", NK );
        throw std::exception();
      }
    }

    template< typename Iterator >
    static std::optional< TotalCrossSection >
    readTotalCrossSection( Iterator& begin,
                           const Iterator& end,
                           long& lineNumber,
                           int MAT,
                           int MF,
                           int MT,
                           int size ) {

      if ( size == 1 ) {

        return std::nullopt;
      }

      return std::make_optional( TotalCrossSection( begin, end, lineNumber,
                                                    MAT, MF, MT ) );
    }

    /* constructor */

    /**
     *  @brief Private constructor
     */
    Type( int MT, int zaid, double awr,
          std::optional< TotalCrossSection >&& total,
          std::vector< PartialCrossSection >&& partials ) :
      Base( zaid, awr, MT ),
      total_( std::move( total ) ),
      partials_( std::move( partials ) ) {

      verifyNK( this->NK() );
    }

    /**
     *  @brief Private constructor
     */
    template< typename Iterator >
    Type( int zaid, double awr,
          std::optional< TotalCrossSection >&& total,
          Iterator& begin, const Iterator& end,
          long& lineNumber, int MAT, int MF, int MT, int NK ) :
      Type( MT, zaid, awr,
            std::move( total ),
            readSequence< PartialCrossSection >( begin, end, lineNumber,
                                                 MAT, MF, MT, NK ) ) {}

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
     *  @brief Constructor (only one partial given, no total required)
     *
     *  @param[in] partial   the partial cross section
     */
    Type( int MT, int zaid, double awr,
          PartialCrossSection&& partial )
      try : Type( MT, zaid, awr, std::nullopt, { std::move( partial ) } ) {}
      catch ( std::exception& e ) {
       Log::info( "Trouble while constructing section {} of File 13", MT );
       throw e;
     }

    /**
     *  @brief Constructor (one total and multiple partials)
     *
     *  @param[in] total      the total photon production cross section
     *  @param[in] partials   the partial photon production cross sections
     */
    Type( int MT, int zaid, double awr,
          TotalCrossSection&& total,
          std::vector< PartialCrossSection >&& partials ) :
      Type( MT, zaid, awr,
            std::make_optional( std::move( total ) ),
            std::move( partials ) ) {}

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
      try : Type( head.ZA(), head.AWR(),
                  readTotalCrossSection( begin, end, lineNumber,
                                         MAT, 13, head.MT(), head.N1() ),
                  begin, end, lineNumber, MAT, 13, head.MT(), head.N1() ) {
        readSEND( begin, end, lineNumber, MAT, 13 );
      } catch ( std::exception& e ) {
        Log::info( "Trouble while reading section {} of File 13 of Material {}",
                   head.MT(), MAT );
        throw e;
      }

    /* get methods */

    /**
     *  @brief Return the number of photons (discrete and continuum) with
     *         partial cross sections
     */
    int NK() const { return this->partials_.size(); }

    /**
     *  @brief Return the number of photons (discrete and continuum) with
     *         partial cross sections
     */
    int numberPhotons() const { return this->NK(); }

    /**
     *  @brief Return the total cross section (optional)
     */
    const OptionalTotalCrossSection& totalCrossSection() const {

      return this->total_;
    }

    /**
     *  @brief Return the partial cross sections
     */
    auto photonPartialCrossSections() const {

      using namespace njoy::tools;
      return std20::views::all( this->partials_ );
    }

    /**
     *  @brief Return the number of lines in this MF13 section
     */
    long NC() const {

      long NC = 1;
      if ( this->total_ ) { NC += this->total_->NC(); }
      for ( const auto& entry : this->partials_ ) { NC += entry.NC(); }
      return NC;
    }

    /**
     *  @brief Print the MF13 section (includes SEND record)
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
      if ( this->total_ ) { this->total_->print( it, MAT, MF, MT ); }
      for ( const auto& entry : this->partials_ ) {

        entry.print( it, MAT, MF, MT );
      }
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
