
template< typename Iterator >
static ResonanceParameters::Range
resolvedRange( const CONT& cont,
               Iterator& it, const Iterator& end, long& lineNumber,
               int MAT, int MF, int MT ){

  Resolved::Base base( cont.C1(), cont.C2(), cont.N1(), cont.N2() );

  switch( cont.L2() ){
    case 1:
      Log::info( "Found SLBW subsection" );
      if( cont.N1() > 0 ){
        TAB1 tab1( it, end, lineNumber, MAT, MF, MT );
        return Resolved::SLBW(std::move(base), std::move( tab1 ), 
                              it, end, lineNumber, MAT, MF, MT );
      }
      else{
        return Resolved::SLBW(std::move(base),
                              it, end, lineNumber, MAT, MF, MT );
      }
      break;
    case 2:
      Log::info( "Found MLBW subsection" );
      if( cont.N1() > 0 ){
        TAB1 tab1( it, end, lineNumber, MAT, MF, MT );
        return Resolved::MLBW(std::move(base), std::move( tab1 ), 
                              it, end, lineNumber, MAT, MF, MT );
      }
      else{
        return Resolved::MLBW(std::move(base),
                              it, end, lineNumber, MAT, MF, MT );
      }
      break;
    case 3:
      Log::info( "Found ReichMoore subsection" );
      if( cont.N1() > 0 ){
        TAB1 tab1( it, end, lineNumber, MAT, MF, MT );
        return Resolved::ReichMoore(std::move(base), std::move( tab1 ), 
                                    it, end, lineNumber, MAT, MF, MT );
      }
      else{
        return Resolved::ReichMoore(std::move(base),
                                    it, end, lineNumber, MAT, MF, MT );
      }
      break;
    case 4:
      Log::info( "Found Adler-Adler subsection" );
      Log::error( "The Adler-Adler representation has not yet been implemented." );
      throw std::exception();
      break;
    case 7:
      Log::info( "Found R-Matrix Limited subsection" );
      Log::error( "The R-Matrix Limited representation has not yet been implemented." );
      throw std::exception();
      break;
    default:
      Log::error( "Encountered invalid LRF: {} for LRU=1", cont.L2() );
      throw std::exception();
      break;
  }
}
