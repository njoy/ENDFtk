#ifndef NJOY_ENDFTK_SECTION_12
#define NJOY_ENDFTK_SECTION_12

// system includes
#include <variant>
#include <optional>

// other includes
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"
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
   *  @brief MF12 - photon production multiplicities and transition probability
   *                arrays
   *
   *  See ENDF102, section 12.2 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 12 > : protected Base {

  public:

    #include "ENDFtk/section/12/TotalMultiplicity.hpp"
    #include "ENDFtk/section/12/PartialMultiplicity.hpp"

    #include "ENDFtk/section/12/Multiplicities.hpp"               // LO=1
    #include "ENDFtk/section/12/TransitionProbabilities.hpp"      // LO=2

    using LO1 = Multiplicities;
    using LO2 = TransitionProbabilities;

    /** @typedef PhotonProduction
     *  @brief The photon production multiplicities or transition probabilities
     *         of MF12
     *
     *  This photon production data class is set up as a variant.
     */
    using PhotonProduction =
              std::variant< Multiplicities,                      // LO=1
                            TransitionProbabilities >;           // LO=2

  private:

    /* fields */

    PhotonProduction photon_;

    /* auxiliary functions */

    template< typename Iterator >
    static PhotonProduction
    readPhotonProduction( Iterator& begin,
                          const Iterator& end,
                          long& lineNumber,
                          int MAT,
                          int MF,
                          int MT,
                          int LO,
                          int N ) {

      switch ( LO ) {
        case 1: return Multiplicities( begin, end, lineNumber, MAT, MF, MT, N );
        case 2: return TransitionProbabilities( begin, end, lineNumber, MAT, MF, MT );
        default : {
          Log::error( "Encountered illegal LO value" );
          Log::info( "LO is either 1 (multiplicities) or 2 (probabilities)" );
          Log::info( "LO value: {}", LO );
          Log::info( "Line number: {}", lineNumber );
          throw std::exception();
        }
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
     *  @param[in] MT            the MT number for the section
     *  @param[in] zaid          the material ZAID value
     *  @param[in] awr           the atomic weight ratio
     *  @param[in] production    the photon production data
     */
    Type( int MT, int zaid, double awr, PhotonProduction&& production ) :
      Base( zaid, awr, MT ), photon_( std::move( production ) ) {}

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
      try : Base( head.ZA(), head.AWR(), head.MT() ),
            photon_( readPhotonProduction( begin, end, lineNumber,
                                           MAT, 12, head.MT(),
                                           head.L1(), head.N1() ) ) {
        readSEND( begin, end, lineNumber, MAT, 12 );
      } catch ( std::exception& e ) {
        Log::info( "Trouble while reading section {} of File 12 of Material {}",
                   head.MT(), MAT );
        throw e;
      }

    /* get methods */

    /**
     *  @brief Return the data type for the photon production data
     */
    int LO() const { return this->photon_.index() + 1; }

    /**
     *  @brief Return the data type for the photon production data
     */
    int representation() const { return this->LO(); }

    /**
     *  @brief Return the photon production data
     */
    const PhotonProduction& photonProduction() const { return this->photon_; }

    /**
     *  @brief Return the number of lines in this MF12 section
     */
    long NC() const {
      long NC = 1
              + std::visit( [&] ( const auto& v )
                                { return v.NC(); }, this->photon_ );
      return NC;
    };

    /**
     *  @brief Print the MF12 section (includes SEND record)
     *
     *  @tparam OutputIterator   an output iterator
     *
     *  @param[in] it            the current position in the output
     *  @param[in] MAT           the MAT number
     *  @param[in] MF            the MF number
     */
    template< typename OutputIterator >
    void print( OutputIterator& it, int MAT, int MF ) const {

      struct L2 {

        int operator()( const Multiplicities& ) { return 0; }
        int operator()( const TransitionProbabilities& value ) {

          return value.LG();
        }
      };

      struct N1 {

        int operator()( const Multiplicities& value ) { return value.NK(); }
        int operator()( const TransitionProbabilities& value ) {

          return value.NT() + 2;
        }
      };

      int MT = this->MT();
      ControlRecord( this->ZA(), this->AWR(), this->LO(),
                     std::visit( L2(), this->photon_ ),
                     std::visit( N1(), this->photon_ ),
                     0 ).print( it, MAT, MF, MT );
      std::visit( [&] ( const auto& v ) -> void
                      { v.print( it, MAT, MF, MT ); },
                  this->photon_ );
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
