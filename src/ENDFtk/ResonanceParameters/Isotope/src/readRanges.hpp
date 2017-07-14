template< typename Iterator >
static EnergyRange
readRange( Iterator& it, const Iterator& end, long& lineNumber,
           int MAT, int MF, int MT ){

  Base base( it, end, lineNumber, MAT, MF, MT );

  switch( base.LRU() ){
  case 0:
    return SpecialCase( base, it, end, lineNumber, MAT, MF, MT );
  case 1: {
    switch( base.LRF() ){
    case 1:
      return Resolved::SLBW( base, it, end, lineNumber, MAT, MF, MT );
    case 2:
      return Resolved::MLBW( base, it, end, lineNumber, MAT, MF, MT );
    case 3:
      return Resolved::ReichMoore( base, it, end, lineNumber, MAT, MF, MT );
    case 4:
      Log::info( "Found Adler-Adler subsection" );
      Log::error( "The Adler-Adler representation has not yet been implemented." );
      throw std::exception();
    case 7:
      Log::info( "Found R-Matrix Limited subsection" );
      Log::error( "The R-Matrix Limited representation has not yet been implemented." );
      throw std::exception();
    }
  }
  case 2:
    Log::info( "Found unresolved region subsection" );
    Log::error( "Unresolved region subsections have not yet been implemented" );
    throw std::exception();
  }

  /* unreachable but necessary to satisfy compiler warning */
  throw std::exception();
}

template< typename Iterator >
static std::vector< EnergyRange >
readRanges( int NER,
            Iterator& it, const Iterator& end, long& lineNumber,
            int MAT, int MF, int MT ){
  std::vector< EnergyRange > ranges;
  if ( NER < 0 ){
    Log::error( "Encountered illegal NER value" );
    Log::info( "NER required to be zero or greater" );
    Log::info( "NER value: {}", NER );
    throw std::exception();
  }
  
  while( NER-- ){
    ranges.push_back( readRange( it, end, lineNumber, MAT, MF, MT ) );
  }
  return ranges;
}
