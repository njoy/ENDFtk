#ifndef NJOY_ENDFTK_SECTION_1_460
#define NJOY_ENDFTK_SECTION_1_460

// system includes
#include <variant>

// other includes
#include "ENDFtk/macros.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief MF1 MT460 - delayed photon data
   *
   *  See ENDF102, section 1.6 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 1, 460 > : 
    protected BaseWithoutMT< Type< 1, 460 > > {

    friend BaseWithoutMT< Type< 1, 460 > >;

  public:

    #include "ENDFtk/section/1/460/DiscretePhotonMultiplicity.hpp"
    #include "ENDFtk/section/1/460/DiscretePhotons.hpp"
    #include "ENDFtk/section/1/460/ContinuousPhotons.hpp"

    using DelayedPhotonData = std::variant< // LO=1
                                            DiscretePhotons,
                                            // LO=2
                                            ContinuousPhotons >;

  protected:

    /* fields */

    DelayedPhotonData data_;

    /* auxiliary functions */

    template< typename Iterator >
    static DelayedPhotonData
    readPhotonData( Iterator& begin,
                    const Iterator& end,
                    long& lineNumber,
                    int MAT,
                    int LO,
                    int NG ) {

      switch ( LO ) {

        case 1 : return DiscretePhotons( begin, end, lineNumber, MAT, 1, 460, NG );
        case 2 : return ContinuousPhotons( begin, end, lineNumber, MAT, 1, 460 );
        default : {

          Log::error( "Encountered illegal LO value" );
          Log::info( "LO must be equal to 1 or 2" );
          Log::info( "LO value: {}", LO );
          Log::info( "Line number: {}", lineNumber - 1 );
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
     *  @param[in] zaid       the ZA value of the material
     *  @param[in] awr        the atomic weight ratio
     *  @param[in] photons    the delayed photon data
     */
    Type( int zaid, double awr, DelayedPhotonData&& photons ) :
      BaseWithoutMT( zaid, awr ), data_( std::move( photons ) ) {}

    /**
     *  @brief Constructor (from a buffer)
     *
     *  @tparam Iterator        a buffer iterator
     *
     *  @param[in] head         the head record of the section
     *  @param[in] begin        the current position in the buffer
     *  @param[in] end          the end of the buffer
     *  @param[in] lineNumber   the current line number
     *  @param[in] MAT          the expected MAT number
     */
    template< typename Iterator >
    Type ( const HEAD& head,
           Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT )
      try: BaseWithoutMT( head, MAT, 1 ),
           data_( readPhotonData( begin, end, lineNumber,
                                  MAT, head.L1(), head.N1() ) ) {

        readSEND( begin, end, lineNumber, MAT, 1 );
      }
      catch( std::exception& e ) {

        Log::info( "Trouble while reading section 460 of File 1 of Material {}",
                   MAT );
        throw e;
      }

    /* methods */

    /**
     *  @brief Return the representation type for the delayed photon data
     */
    int LO() const { return std::visit( [] ( const auto& v ) -> long
                                           { return v.LO(); },
                                        this->data_ ); }

    /**
     *  @brief Return the representation type for the delayed photon data
     */
    int representation() const { return this->LO(); }

    /**
     *  @brief Return the number of discrete photons
     */
    int NG() const { return std::visit( [] ( const auto& v ) -> long
                                           { return v.NG(); },
                                        this->data_ ); }

    /**
     *  @brief Return the number of discrete photons
     */
    int numberDiscretePhotons() const { return this->NG(); }

    /**
     *  @brief Return the delayed photon data
     */
    const DelayedPhotonData& delayedPhotons() const { return this->data_; }

    /**
     *  @brief Return the number of lines in this MF1/MT460 section
     */
    long NC() const { return 1 + std::visit( [] ( const auto& v ) -> long
                                                { return v.NC(); },
                                             this->data_ ); }

    /**
     *  @brief Print the MF1/MT458 section (includes SEND record)
     *
     *  @tparam OutputIterator   an output iterator
     *
     *  @param[in] it            the current position in the output
     *  @param[in] MAT           the MAT number
     *  @param[in] MF            the MF number
     */
    template< typename OutputIterator >
    void print( OutputIterator& it, int MAT, int MF ) const {

      ControlRecord( this->ZA(), this->AWR(), this->LO(),
                     0, this->NG(), 0 ).print( it, MAT, MF, MT() );
      std::visit( [&] ( const auto& v ) -> void
                      { v.print( it, MAT, MF, MT() ); },
                  this->data_ );
      SEND( MAT, MF ).print( it );
    }

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber(){ return 460; }

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
