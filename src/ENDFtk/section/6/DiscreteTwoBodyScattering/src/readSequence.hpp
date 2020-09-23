template< typename Iterator >
static std::vector< Variant >
readSequence( long nep,
              Iterator& begin,
              const Iterator& end,
              long& lineNumber,
              int MAT,
              int MF,
              int MT ) {

  std::vector< Variant > sequence;
  sequence.reserve( nep );

  while( nep-- ) {

    ListRecord list( begin, end, lineNumber, MAT, MF, MT );
    switch ( list.L1() ) {

      case 0 : sequence.emplace_back(
                  LegendreCoefficients( std::move( list ) ) );
                  break;
      case 12 :
      case 14 : sequence.emplace_back(
                  Tabulated( std::move( list ) ) );
                  break;
      default : {

        Log::error( "Encountered illegal LANG value" );
        Log::info( "LANG must be equal to 0, 12 or 14" );
        Log::info( "LANG value: {}", list.L1() );
        Log::info( "Line number: {}", lineNumber - list.NC() );
        throw std::exception();
      }
    }
  }

  return sequence;
}
