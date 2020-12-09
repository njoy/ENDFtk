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
