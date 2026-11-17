#ifndef NJOY_ENDFTK_SECTION_1_455
#define NJOY_ENDFTK_SECTION_1_455

// system includes
#include <variant>

// other includes
#include "ENDFtk/macros.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/InterpolationSequenceRecord.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/section.hpp"
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"

#include "ENDFtk/section/1/PolynomialMultiplicity.hpp"
#include "ENDFtk/section/1/TabulatedMultiplicity.hpp"
#include "ENDFtk/section/1/readMultiplicity.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief MF1 MT455 - the number of delayed fission neutrons
   *
   *  See ENDF102, section 1.3 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 1, 455 > :
    protected BaseWithoutMT< Type< 1, 455 > > {

    friend BaseWithoutMT< Type< 1, 455 > >;

  public:

    #include "ENDFtk/section/1/455/EnergyIndependentConstants.hpp"
    #include "ENDFtk/section/1/455/DecayConstants.hpp"
    #include "ENDFtk/section/1/455/EnergyDependentConstants.hpp"

    using DecayConstantData = std::variant< EnergyIndependentConstants, // LDG=0
                                            EnergyDependentConstants >; // LDG=1

    using Multiplicity = std::variant< PolynomialMultiplicity,  // LNU=1
                                       TabulatedMultiplicity >; // LNU=2

  private:

    /* fields */

    DecayConstantData lambda_;
    Multiplicity nubar_;

    /* auxiliary functions */

    template< typename Iterator >
    static DecayConstantData
    readDecayConstantData( Iterator& begin,
                           const Iterator& end,
                           long& lineNumber,
                           int MAT,
                           int MF,
                           int MT,
                           int LDG ) {
      switch ( LDG ) {
        case 0 : return EnergyIndependentConstants( begin, end, lineNumber, MAT, MF, MT );
        case 1 : return EnergyDependentConstants( begin, end, lineNumber, MAT, MF, MT );
        default : {
          Log::error( "Encountered illegal LDG value" );
          Log::info( "LDG must be equal to 0 or 1" );
          Log::info( "LDG value: {}", LDG );
          Log::info( "Line number: {}", lineNumber - 1 );
          throw std::exception();
        }
      }
    }

    /* constructor */

    /**
     *  @brief Private intermediate constructor
     */
    template< typename Iterator >
    Type( int zaid, double awr, DecayConstantData&& constants,
          Iterator& begin, const Iterator& end, long& lineNumber,
          int MAT, int LNU ) :
      Type( zaid, awr, std::move( constants ),
            readMultiplicity( begin, end, lineNumber, MAT, 1, 455, LNU ) ) {}

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
     *  @param[in] zaid            the ZA value of the material
     *  @param[in] awr             the atomic weight ratio
     *  @param[in] constants       the decay constant data
     *  @param[in] multiplicity    the multiplicity data
     */
    Type( int zaid, double awr, DecayConstantData&& constants,
          Multiplicity&& multiplicity ) :
      BaseWithoutMT( zaid, awr ), lambda_( std::move( constants ) ),
      nubar_( std::move( multiplicity ) ) {}

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
    Type( const HEAD& head,
          Iterator& begin,
          const Iterator& end,
          long& lineNumber,
          int MAT )
      try: Type( head.ZA(), head.AWR(),
                 readDecayConstantData( begin, end, lineNumber,
                                        MAT, 1, 455, head.L1() ),
                 begin, end, lineNumber, MAT, head.L2() ) {

        readSEND( begin, end, lineNumber, MAT, 1 );
      } catch( std::exception& e ) {

        Log::info( "Trouble while constructing section 455 of File 1 of Material {}",
                   MAT );
        throw e;
      }

    /* methods */

    /**
     *  @brief Return the fission multiplicity representation type
     */
    int LNU() const { return std::visit( [] ( const auto& v ) -> long
                                            { return v.LNU(); },
                                         this->nubar_ ); }

    /**
     *  @brief Return the fission multiplicity representation type
     */
    int representation() const { return this->LNU(); }

    /**
     *  @brief Return the type of decay constants
     */
    int LDG() const { return std::visit( [] ( const auto& v ) -> long
                                            { return v.LDG(); },
                                         this->lambda_ ); }

    /**
     *  @brief Return the type of decay constants
     */
    int type() const { return this->LDG(); }

    /**
     *  @brief Return the decay constant data for the delayed precursor groups
     */
    const DecayConstantData& delayedGroups() const { return this->lambda_; }

    /**
     *  @brief Return the fission multiplicity data
     */
    const Multiplicity& nubar() const { return this->nubar_; }

    /**
     *  @brief Return the number of lines in this MF1/MT455 section
     */
    long NC() const { return 1 + std::visit( [] ( const auto& v ) -> long
                                                { return v.NC(); },
                                             this->lambda_ )
                               + std::visit( [] ( const auto& v ) -> long
                                                { return v.NC(); },
                                             this->nubar_ ); }

    /**
     *  @brief Print the MF1/MT455 section (includes SEND record)
     *
     *  @tparam OutputIterator   an output iterator
     *
     *  @param[in] it            the current position in the output
     *  @param[in] MAT           the MAT number
     *  @param[in] MF            the MF number
     */
    template< typename OutputIterator >
    void print( OutputIterator& it, int MAT, int MF ) const {

      ControlRecord( this->ZA(), this->AWR(), this->LDG(),
                     this->LNU(), 0, 0 ).print( it, MAT, MF, MT() );
      std::visit( [&] ( const auto& v ) -> void
                      { v.print( it, MAT, MF, MT() ); },
                  this->lambda_ );
      std::visit( [&] ( const auto& v ) -> void
                      { v.print( it, MAT, MF, MT() ); },
                  this->nubar_ );
      SEND( MAT, MF ).print( it );
    }

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber(){ return 455; }

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
