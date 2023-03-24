template< typename Iterator >
static std::vector< LegendreCoefficients >
readSequence( long lang,
              long nep,
              Iterator& begin,
              const Iterator& end,
              long& lineNumber,
              int MAT,
              int MF,
              int MT ) {

  std::vector< LegendreCoefficients > sequence;
  sequence.reserve( nep );

  if ( lang != 1 ) {

    Log::error( "Encountered illegal LANG value" );
    Log::info( "LANG must be equal to 1 for LAW=1" );
    Log::info( "LANG value: {}", lang );
    throw std::exception();
  }

  while( nep-- ) {

    sequence.emplace_back(
        LegendreCoefficients( begin, end, lineNumber, MAT, MF, MT ) );
  }

  return sequence;
}
