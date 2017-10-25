template< typename Iterator >
ThermalPoint ( Iterator& begin,
               const Iterator& end,
               long& lineNumber,
               int MAT,
               int MF,
               int MT ) :
  ListRecord( begin, end, lineNumber, MAT, MF, MT ) {
    if ( ListRecord::NPL() != 18 ) {
      Log::error( "Encountered illegal NPL value" );
      Log::info( "NPL must be equal to 18" );
      Log::info( "NPL value: {}", ListRecord::NPL() );
      Log::info( "Line number: {}", lineNumber - ListRecord::NC() );
      throw std::exception();
    }
  }

ThermalPoint ( ListRecord&& list ) :  ListRecord( std::move( list ) ) {}

