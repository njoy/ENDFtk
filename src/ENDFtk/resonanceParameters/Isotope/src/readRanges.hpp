template< typename Iterator >
static std::vector< ResonanceRange >
readRanges( Iterator& begin, const Iterator& end, long& lineNumber,
            int MAT, int MF, int MT,
            int LFW, int NER ) {

  std::vector< ResonanceRange > ranges;

  if ( NER < 0 ) {

    Log::error( "Encountered illegal NER value" );
    Log::info( "NER required to be zero or greater" );
    Log::info( "NER value: {}", NER );
    throw std::exception();
  }

  ranges.reserve( NER );

  while( NER-- ) {

    ControlRecord cont( begin, end, lineNumber, MAT, MF, MT );
    double EL = cont.C1();
    double EH = cont.C2();
    int LRU = cont.L1();
    int LRF = cont.L2();
    int NRO = cont.N1();
    int NAPS = cont.N2();

    std::optional< ScatteringRadius > radius =
        readScatteringRadius( begin, end, lineNumber, MAT, MF, MT, NRO );

    ResonanceRange::ResonanceParameters parameters =
        readParameters( begin, end, lineNumber, MAT, MF, MT, LRU, LRF, LFW );

    ranges.emplace_back( EL, EH, NAPS,
                         std::move( parameters ), std::move( radius ) );
  }
  return ranges;
}
