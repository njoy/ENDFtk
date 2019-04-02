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
    case 1 : return NuclearAmplitudeExpansion( std::move( list ) );
    case 2 : return LegendreCoefficients( std::move( list ) );
    case 12 :
    case 14 :
    case 15 : return NuclearPlusInterference( std::move( list ) );
    default : {
      Log::error( "Encountered illegal LTP value" );
      Log::info( "LTP must be equal to 1, 2, 12, 14 or 15" );
      Log::info( "LTP value: {}", list.L1() );
      Log::info( "Line number: {}", lineNumber - list.NC() );
      throw std::exception();
    }
  }
}