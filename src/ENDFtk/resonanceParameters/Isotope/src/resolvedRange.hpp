template< typename Iterator >
static Range
readRange( Iterator& it, const Iterator& end, long& lineNumber,
           int MAT, int MF, int MT ){

  resolved::Base base( it, end, lineNumber, MAT, MF, MT );

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
static std::vector< Range >
readRanges( int NER,
            Iterator& it, const Iterator& end, long& lineNumber,
            int MAT, int MF, int MT ){
  std::vector< EnergyRange > ranges;
  assert( NER >= 0 );
  while( NER-- ){
    ranges.push_back( readRange( it, end, lineNumber, MAT, MF, MT ) );
  }
  return ranges;
}
