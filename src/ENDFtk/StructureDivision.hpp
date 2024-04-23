#ifndef NJOY_ENDFTK_STRUCTUREDIVISION
#define NJOY_ENDFTK_STRUCTUREDIVISION

// system includes

// other includes
#include "tools/Log.hpp"
#include "ENDFtk/record.hpp"

namespace njoy {
namespace ENDFtk {

  class StructureDivision {

  public:

    /* convenience typedefs */
    using Base =
      record::Base< record::Real, record::Real,
                    record::Integer<11>, record::Integer<11>,
                    record::Integer<11>, record::Integer<11> >;

    using Tail = record::Tail;

    /* fields */
    Base base;
    Tail tail;

    StructureDivision( double C1, double C2, long L1, long L2, long N1, long N2,
                       int MAT, int MF, int MT ) :
      base( C1, C2, L1, L2, N1, N2 ),
      tail( MAT, MF, MT ) {}

    template< typename Iterator >
    StructureDivision( Iterator& it, const Iterator& end, long& lineNumber ) :
      StructureDivision( it, it, end, lineNumber ) {}

    template< typename Iterator >
    StructureDivision
    ( Iterator begin, Iterator& it, const Iterator& end, long& lineNumber )
      try : base( it, end ), tail( it, end, lineNumber ) {

        if (tail.material() < -1) {

          Log::error( "Illegal material number (MAT) encountered" );
          Log::info( "Error parsing line {}: \"{}\"",
                     lineNumber - 1,
                     std::string( begin, std::find( begin, end, '\n' ) ) );
          Log::info( "Material numbers are greater than or equal to -1" );
          Log::info( "Material number: {}", this->tail.material() );
          throw std::exception();
        }
        if (tail.file() < 0) {

          Log::error( "Illegal file number (MF) encountered" );
          Log::info( "Error parsing line {}: \"{}\"",
                     lineNumber - 1,
                     std::string( begin, std::find( begin, end, '\n' ) ) );
          Log::info( "File numbers are greater than or equal to 0" );
          Log::info( "File number: {}", this->tail.file() );
          throw std::exception();
        }
        if (tail.section() < 0) {

          Log::error( "Illegal section number (MT) encountered" );
          Log::info( "Error parsing line {}: \"{}\"",
                     lineNumber - 1,
                     std::string( begin, std::find( begin, end, '\n' ) ) );
          Log::info( "Section numbers are greater than or equal to 0" );
          Log::info( "Section number: {}", this->tail.section() );
          throw std::exception();
        }
      }
      catch ( int fieldNumber ) {

        switch (fieldNumber) {
        case 6 :

          Log::error( "Illegal material number (MAT) encountered" );
          Log::info( "Error while parsing line {}:", lineNumber - 1 );
          Log::info( "Line {}:", std::string( begin, std::find( begin, end, '\n' ) ) );
          break;
        case 7 :

          Log::error( "Illegal file number (MF) encountered" );
          Log::info( "Error while parsing line {}:", lineNumber - 1 );
          Log::info( "Line {}:", std::string( begin, std::find( begin, end, '\n' ) ) );
          break;
        case 8 :

          Log::error( "Illegal section number (MT) encountered" );
          Log::info( "Error while parsing line {}:", lineNumber - 1 );
          Log::info( "Line {}:", std::string( begin, std::find( begin, end, '\n' ) ) );
          break;
        default:
          break;
        }
        throw std::exception();
      }
      catch ( std::exception& e ) {

        Log::info( "Error encountered while constructing structure division" );
        throw e;
      }

    bool isHead() const {

      return this->tail.section() and this->tail.file() and this->tail.material();
    }

    bool isSendPermissive() const {

      const static Base empty(0.0, 0.0, 0, 0, 0, 0);
      return ( this->base == empty ) and ( this->tail.section() == 0 );
    };

    bool isSend() const {

      return this->isSendPermissive()
             and this->tail.file()
             and ( this->tail.material() > 0 );
    }

    bool isFendPermissive() const {

      return this->isSendPermissive() and ( this->tail.file() == 0 );
    }

    bool isFend() const {

      return this->isFendPermissive() and ( this->tail.material() > 0 );
    }

    bool isMend() const {

      return this->isFendPermissive() and ( this->tail.material() == 0 );
    }

    bool isTend() const {

      return this->isFendPermissive() and ( this->tail.material() == -1 );
    }

    template< typename OutputIterator >
    void print( OutputIterator& it ) const {

      using namespace njoy::tools;
      if ( this->isHead() ) {

        using Format = disco::Record< disco::ENDF, disco::ENDF,
                                      disco::Integer< 11 >, disco::Integer< 11 >,
                                      disco::Integer< 11 >, disco::Integer< 11 >,
                                      disco::Integer< 4 >, disco::Integer< 2>,
                                      disco::Integer< 3 >,
                                      disco::Column<5> >;
        Format::write( it, std::get< 0 >( this->base.fields ),
                           std::get< 1 >( this->base.fields ),
                           std::get< 2 >( this->base.fields ),
                           std::get< 3 >( this->base.fields ),
                           std::get< 4 >( this->base.fields ),
                           std::get< 5 >( this->base.fields ),
                           this->tail.MAT(), this->tail.MF(), this->tail.MT() );
      }
      else {

        using Format = disco::Record< disco::Integer< 70 >,
                                      disco::Integer< 2 >,
                                      disco::Integer< 3 >,
                                      disco::Column<5> >;
        Format::write( it, this->tail.MAT(), this->tail.MF(), this->tail.MT() );
      }
    }
  };

  inline StructureDivision sectionEndRecord( int MAT, int MF ) {

    if ( MAT < 1 ) {

      Log::error( "Illegal material number (MAT) specified in SEND record" );
      Log::info( "SEND records require a material number greater than 0" );
      Log::info( "Specified material number: {}", MAT );
      throw std::exception();
    }
    if ( MF < 1 ) {

      Log::error( "Illegal file number (MF) specified in SEND record" );
      Log::info( "SEND records require a file number greater than 0" );
      Log::info( "Specified file number: {}", MF );
      throw std::exception();
    }
    return StructureDivision( 0.0, 0.0, 0, 0, 0, 0, MAT, MF, 0 );
  }

  inline StructureDivision SEND( int MAT, int MF ) {

    return sectionEndRecord( MAT, MF );
  }

  inline StructureDivision fileEndRecord( int MAT ) {

    if ( MAT < 1 ) {

      Log::error( "Illegal material number (MAT) specified in FEND record" );
      Log::info( "FEND records require a material number greater than 0" );
      Log::info( "Specified material number: {}", MAT );
      throw std::exception();
    }
    return StructureDivision( 0.0, 0.0, 0, 0, 0, 0, MAT, 0, 0 );
  }

  inline StructureDivision FEND( int MAT ) { return fileEndRecord( MAT ); }

  inline StructureDivision materialEndRecord() {

    return StructureDivision( 0.0, 0.0, 0, 0, 0, 0, 0, 0, 0 );
  }

  inline StructureDivision MEND() { return materialEndRecord(); }

  inline StructureDivision tapeEndRecord() {

    return StructureDivision( 0.0, 0.0, 0, 0, 0, 0, -1, 0, 0 );
  }

  inline StructureDivision TEND() { return tapeEndRecord(); }

} // ENDFtk namespace
} // njoy namespace

#endif
