static void
verifySize( int NL, int NL1, int NSS, bool diag ) {

  if ( diag ) {

    if ( NL != NL1 ) {

      Log::error( "Encountered illegal NL1 value" );
      Log::info( "NL1 must be same as NL when MT==MT1" );
      Log::info( "NL value: {}", NL );
      Log::info( "NL1 value: {}", NL1 );
      throw std::exception();
    }
    if ( NL*(NL+1)/2 != NSS ) {

      Log::error( "Incorrect number of L-blocks" );
      Log::info( "Must be NL*(NL+1)/2 L-blocks when MT==MT1" );
      Log::info( "NL value: {}", NL );
      Log::info( "Number blocks: {}", NSS );
      throw std::exception();
    }
  }
  else {

    if ( NL*NL1 != NSS ) {

      Log::error( "Incorrect number of L-blocks" );
      Log::info( "Must be NL*NL1 L-blocks when MT!=MT1" );
      Log::info( "NL value: {}", NL );
      Log::info( "NL1 value: {}", NL1 );
      Log::info( "Number blocks: {}", NSS );
      throw std::exception();
    }
  }
}
