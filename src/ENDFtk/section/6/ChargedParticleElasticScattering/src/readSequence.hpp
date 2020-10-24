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

      case 1 : sequence.emplace_back(
                  NuclearAmplitudeExpansion( std::move( list ) ) );
                  break;
      case 2 : sequence.emplace_back(
                  LegendreCoefficients( std::move( list ) ) );
                  break;
      case 12 :
      case 14 :
      case 15 : sequence.emplace_back(
                  NuclearPlusInterference( std::move( list ) ) );
                  break;
      default : {

        Log::error( "Encountered illegal LTP value" );
        Log::info( "LTP must be equal to 1, 2, 12, 14 or 15" );
        Log::info( "LTP value: {}", list.L1() );
        Log::info( "Line number: {}", lineNumber - list.NC() );
        throw std::exception();
      }
    }
  }

  return sequence;
}
