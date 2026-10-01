#ifndef NJOY_ENDFTK_SECTION_1_458
#define NJOY_ENDFTK_SECTION_1_458

// system includes
#include <variant>
#include <optional>

// other includes
#include "ENDFtk/macros.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/section.hpp"
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief MF1 MT458 - energy release from fission
   *
   *  See ENDF102, section 1.5 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 1, 458 > :
    protected BaseWithoutMT< Type< 1, 458 > > {

    friend BaseWithoutMT< Type< 1, 458 > >;

  public:

    #include "ENDFtk/section/1/458/ThermalPointComponents.hpp"
    #include "ENDFtk/section/1/458/PolynomialComponents.hpp"
    #include "ENDFtk/section/1/458/EnergyReleaseComponent.hpp"
    #include "ENDFtk/section/1/458/TabulatedComponents.hpp"

    using FissionEnergyReleaseData = std::variant< // LFC=0 NPLY=0
                                                   ThermalPointComponents,
                                                   // LFC=0 NPLY!=0
                                                   PolynomialComponents,
                                                   // LFC=1 NPLY=0
                                                   TabulatedComponents >;

  protected:

    /* fields */

    FissionEnergyReleaseData data_;

    /* auxiliary functions */

    template< typename Iterator >
    static FissionEnergyReleaseData
    readFissionEnergyReleaseData( Iterator& begin,
                                  const Iterator& end,
                                  long& lineNumber,
                                  int MAT,
                                  int LFC,
                                  int NFC ) {

      switch ( LFC ) {

        case 0 : {

          ListRecord list( begin, end, lineNumber, MAT, 1, 458 );
          if ( list.NPL() != ( list.L2() + 1 ) * 18 ) {

            Log::error( "Encountered illegal NPL value" );
            Log::info( "NPL must be equal to {}", ( list.L2() + 1 ) * 18 );
            Log::info( "NPL value: {}", list.NPL() );
            Log::info( "Line number: {}", lineNumber - list.NC() );
            throw std::exception();
          }
          if ( list.L2() == 0 ) {

            return ThermalPointComponents( std::move( list ) );
          }
          else {

            return PolynomialComponents( std::move( list ) );
          }
        }
        case 1 : return TabulatedComponents( begin, end, lineNumber, MAT, 1, 458, NFC );
        default : {

          Log::error( "Encountered illegal LFC value" );
          Log::info( "LFC must be equal to 0 or 1" );
          Log::info( "LFC value: {}", LFC );
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
     *  @param[in] zaid        the ZA value of the material
     *  @param[in] awr         the atomic weight ratio
     *  @param[in] fissionq    the fission energy release data
     */
    Type( int zaid, double awr, FissionEnergyReleaseData&& fissionq ) :
      BaseWithoutMT( zaid, awr ), data_( std::move( fissionq ) ) {}

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
           data_( readFissionEnergyReleaseData( begin, end, lineNumber, MAT,
                                                head.L2(), head.N2() ) ) {

        readSEND( begin, end, lineNumber, MAT, 1 );
      }
      catch( std::exception& e ) {

        Log::info( "Trouble while constructing section 458 of File 1 of Material {}",
                   MAT );
        throw e;
      }

    /* methods */

    /**
     *  @brief Return the tabulated energy release flag
     */
    int LFC() const { return std::visit( [] ( const auto& v ) -> long
                                            { return v.LFC(); },
                                         this->data_ ); }

    /**
     *  @brief Return the tabulated energy release flag
     */
    bool tabulatedEnergyRelease() const { return this->LFC(); }

    /**
     *  @brief Return the polynomial expansion order
     */
    int NFC() const { return std::visit( [] ( const auto& v ) -> long
                                            { return v.NFC(); },
                                         this->data_ ); }

    /**
     *  @brief Return the number of tabulated energy release components
     */
    int numberTabulatedComponents() const { return this->NFC(); }

    /**
     *  @brief Return the number of tabulated energy release components
     */
    int NPLY() const { return std::visit( [] ( const auto& v ) -> long
                                             { return v.NPLY(); },
                                          this->data_ ); }

    /**
     *  @brief Return the polynomial expansion order
     */
    int order() const { return this->NPLY(); }

    /**
     *  @brief Return the fission energy release data
     */
    const FissionEnergyReleaseData& energyRelease() const {

      return this->data_;
    }

    /**
     *  @brief Return the number of lines in this MF1/MT458 section
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

      ControlRecord( this->ZA(), this->AWR(), 0,
                     this->LFC(), 0, this->NFC() ).print( it, MAT, MF, MT() );
      std::visit( [&] ( const auto& v ) -> void
                      { v.print( it, MAT, MF, MT() ); },
                  this->data_ );
      SEND( MAT, MF ).print( it );
    }

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber(){ return 458; }

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
