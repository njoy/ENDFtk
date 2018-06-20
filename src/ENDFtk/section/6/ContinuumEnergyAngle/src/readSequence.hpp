template< typename Iterator >
static std::vector< SubSection >
readSequence( long lang,
              long nep,
              Iterator& begin,
              const Iterator& end,
              long& lineNumber,
              int MAT,
              int MF,
              int MT ) {

  std::vector< SubSection > sequence;
  sequence.reserve( nep );

  while( nep-- ) {
    switch ( lang ) {
      case 1 : sequence.emplace_back(
                  LegendreCoefficients( begin, end, lineNumber, MAT, MF, MT ) );
                  break;
      case 2 : sequence.emplace_back(
                  KalbachMann( begin, end, lineNumber, MAT, MF, MT ) );
                  break;
      case 11 :
      case 12 :
      case 13 :
      case 14 :
      case 15 : sequence.emplace_back(
                  Tabulated( lang, begin, end, lineNumber, MAT, MF, MT ) );
                  break;
      default : break; /* unreachable */
    }
  }

  return sequence;
}

