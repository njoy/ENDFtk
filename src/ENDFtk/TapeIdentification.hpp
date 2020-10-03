#ifndef NJOY_ENDFTK_TAPEIDENTIFICATION
#define NJOY_ENDFTK_TAPEIDENTIFICATION

// system includes

// other includes
#include "Log.hpp"
#include "ENDFtk/record.hpp"

namespace njoy {
namespace ENDFtk {

  class TapeIdentification {

    /* fields */
    record::Base< record::Character< 66 > > base;
    record::TailVerifying< record::MT, record::MF > tail;

  public:

    /* constructor */

    TapeIdentification( std::string&& text, int tapeNumber ) :
      base( std::move(text) ), tail( tapeNumber, 0, 0 ){}

    template< typename Iterator >
    TapeIdentification( Iterator& it, const Iterator& end, long& lineNumber )
      try:
        base( it, end ),
        tail( 0, 0, it, end, lineNumber )
      {
      } catch ( std::exception& e ) {
        Log::info( "Encountered trouble when reading TapeIdentification" );
        throw e;
      } catch ( int fieldNo ){
        --lineNumber;
        /* TODO error information here */
        throw std::exception();
      }

    /* methods */
    
    std::string& text(){ return std::get<0>( base.fields ); }
    const std::string& text() const { return std::get<0>( base.fields ); }

    int& tapeNumber() { return this->tail.material(); }
    int tapeNumber() const { return this->tail.material(); }

    int& NTAPE(){ return this->tapeNumber(); }
    int NTAPE() const { return this->tapeNumber(); }

    long NC() const { return 1; }

    #include "ENDFtk/TapeIdentification/src/print.hpp"
  };

  using TPID = TapeIdentification;

} // ENDFtk namespace
} // njoy namespace

#endif
