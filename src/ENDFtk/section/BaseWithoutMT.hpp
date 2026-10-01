#ifndef NJOY_ENDFTK_SECTION_BASEWITHOUTMT
#define NJOY_ENDFTK_SECTION_BASEWITHOUTMT

// system includes

// other includes
#include "ENDFtk/HeadRecord.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  template < typename Derived >
  class BaseWithoutMT {

    /* fields */

    int ZA_;
    double atomicWeightRatio_;

  protected:

    /* constructor */

    //! @todo pybind11 variant needs default constructor workaround
    #ifdef PYBIND11
    /**
     *  @brief Default constructor - only enabled for pybind11
     */
    BaseWithoutMT() = default;
    #endif

    BaseWithoutMT( int ZA, double AWR ) :
      ZA_( ZA ), atomicWeightRatio_( AWR ) {

      if ( ZA < 1 ) {

        Log::error( "Illegal ZA number" );
        Log::info( "ZA numbers must be greater than zero" );
        Log::info( "Encountered ZA number: {}", ZA );
        throw std::exception();
      }
      if ( AWR < 0.0 ) {

        Log::error( "Illegal atomic mass ratio" );
        Log::info( "atomic mass ratio numbers must be greater than zero" );
        Log::info( "Encountered atomic mass ratio: {}", AWR );
        throw std::exception();
      }
    }

    BaseWithoutMT( const HEAD& head, int MAT, int MF ) :
      BaseWithoutMT( head.ZA(), head.atomicWeightRatio() ) {

      if ( MAT != head.MAT() ) {

        Log::error( "Incorrect Material number (MAT)." );
        Log::info( "Expected MAT = {}", MAT );
        Log::info( "Encountered MAT = {}", head.MAT() );
        throw std::exception();
      }
      if ( MF != head.MF() ) {

        Log::error( "Incorrect File number (MF)." );
        Log::info( "Expected MF = {}", MF );
        Log::info( "Encountered MF = {}", head.MF() );
        throw std::exception();
      }
    }

  public:

    /* get methods */

    /**
     *  @brief Return the MT number of the section
     */
    constexpr int MT() const {

        return static_cast< const Derived* >( this )->sectionNumber();
    }

    /**
     *  @brief Return the ZA identifier of the section
     */
    constexpr int ZA() const { return this->ZA_; }

    /**
     *  @brief Return the ZA identifier of the section
     */
    constexpr int targetIdentifier() const { return this->ZA(); }

    /**
     *  @brief Return the atomic weight ratio
     */
    constexpr double AWR() const { return this->atomicWeightRatio_; }

    /**
     *  @brief Return the atomic weight ratio
     */
    constexpr double atomicWeightRatio() const { return this->AWR(); }

    template< typename Iterator >
    static void readSEND
    ( Iterator& it, const Iterator& end, long& lineNumber, int MAT, int MF ) {

      try {

        const auto begin = it;
        auto division = StructureDivision( it, end, lineNumber );
        if ( not division.isSend() ) {

          Log::error( "Malformatted SEND record." );
          Log::info( "Error parsing line {}: \"{}\"",
                     lineNumber - 1,
                     std::string( begin, std::find( begin, end, '\n' ) ) );
          throw std::exception();
        }

        if ( MAT != division.tail.MAT() ) {

          Log::error( "Incorrect Material number (MAT) in SEND record." );
          Log::info( "Expected MAT = {}", MAT );
          Log::info( "Encountered MAT = {}", division.tail.MAT() );
          throw std::exception();
        }

        if ( MF != division.tail.MF() ) {

          Log::error( "Incorrect File number (MF) in SEND record" );
          Log::info( "Expected MF = {}", MF );
          Log::info( "Encountered MF = {}", division.tail.MF() );
          throw std::exception();
        }
      }
      catch ( std::exception& e ) {

        Log::info( "Encountered error while reading the SEND record." );
        throw e;
      }
    }

    template<typename Iterator>
    static void readFendOrSend
    ( Iterator&it, const Iterator& end, long& lineNumber, int MAT, int MF ) {

      try {

        const auto begin = it;
        auto division = StructureDivision(it, end, lineNumber);
        if ( ( ! division.isFend() ) && ( ! division.isSend() ) ) {

            Log::error( "Malformatted FEND or SEND record.");
            Log::info( "Error parsing line {}: \"{}\"",
                       lineNumber - 1,
                       std::string( begin, std::find( begin, end, '\n' ) ) );
            throw std::exception();
        }

        if ( MAT != division.tail.MAT() ) {

            Log::error("Incorrect Material number (MAT) in FEND record.");
            Log::info("Expected MAT = {}", MAT);
            Log::info("Encountered MAT = {}", division.tail.MAT());
            throw std::exception();
        }

        if ( division.isSend() && MF != division.tail.MF() ) {

          Log::error( "Incorrect File number (MF) in SEND record" );
          Log::info( "Expected MF = {}", MF );
          Log::info( "Encountered MF = {}", division.tail.MF() );
          throw std::exception();
        }
      }
      catch (std::exception& e) {

        Log::info( "Encountered error while reading the FEND record." );
        throw e;
      }
    }
    
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
