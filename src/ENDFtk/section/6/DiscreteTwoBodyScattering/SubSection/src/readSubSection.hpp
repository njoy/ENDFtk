template< typename Iterator >
static SubSectionVariant
readSubSection( Iterator& begin,
                const Iterator& end,
                long& lineNumber,
                int MAT,
                int MF,
                int MT ) {
  ListRecord list( begin, end, lineNumber, MAT, MF, MT );
  switch ( list.L1() ) {
    case 0 : return LegendreCoefficients( std::move( list ) );
    case 12 :
    case 14 : return Tabulated( std::move( list ) );
    default : {
      Log::error( "Encountered illegal LANG value" );
      Log::info( "LANG must be equal to 0, 12 or 14" );
      Log::info( "LANG value: {}", list.L1() );
      Log::info( "Line number: {}", lineNumber - list.NC() );
      throw std::exception();
    }
  }
}
