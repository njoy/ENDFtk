/*protected:
template< typename Iterator >
static EnergyRange
readRange( int LFW,
           Iterator& it, const Iterator& end, long& lineNumber,
           int MAT, int MF, int MT ){

  Base base( it, end, lineNumber, MAT, MF, MT );

  switch( base.LRU() ){
  case 0:
    return SpecialCase( base, it, end, lineNumber, MAT, MF, MT );
  case 1: {
    switch( base.LRF() ){
    case 1:
      return resolved::SLBW( base, it, end, lineNumber, MAT, MF, MT );
    case 2:
      return resolved::MLBW( base, it, end, lineNumber, MAT, MF, MT );
    case 3:
      return resolved::ReichMoore( base, it, end, lineNumber, MAT, MF, MT );
    case 4:
      Log::info( "Found Adler-Adler subsection" );
      Log::error(
          "The Adler-Adler representation has not yet been implemented." );
      throw std::exception();
    case 7:
      Log::info( "Found R-Matrix Limited subsection" );
      Log::error(
          "The R-Matrix Limited representation has not yet been implemented." );
      throw std::exception();
    }
  }
  case 2: {
    switch( base.LRF() ){
    case 1:
      switch( LFW ){
      case 0:
        return unresolved::EnergyIndependent(
          base, it, end, lineNumber, MAT, MF, MT );
      case 1:
        return unresolved::EnergyDependentFissionWidths(
          base, it, end, lineNumber, MAT, MF, MT );
      default:
        Log::error( "Invalid LFW value ({}) in LRU=2,LRF=1.", LFW );
        throw std::exception();
      }
    case 2:
      return unresolved::EnergyDependent(
          base, it, end, lineNumber, MAT, MF, MT );
    }
  }
  }

  // unreachable but necessary to satisfy compiler warning
  throw std::exception();
}*/

template< typename Iterator >
static std::vector< ResonanceRange >
readRanges( const CONT& cont,
            Iterator& it, const Iterator& end, long& lineNumber,
            int MAT, int MF, int MT ){
  std::vector< ResonanceRange > ranges;

  auto NER = cont.N1();
  if ( NER < 0 ){
    Log::error( "Encountered illegal NER value" );
    Log::info( "NER required to be zero or greater" );
    Log::info( "NER value: {}", NER );
    throw std::exception();
  }

  ranges.reserve( NER );

  while( NER-- ){
    ranges.emplace_back( it, end, lineNumber, MAT, MF, MT );
  }
  return ranges;
}
