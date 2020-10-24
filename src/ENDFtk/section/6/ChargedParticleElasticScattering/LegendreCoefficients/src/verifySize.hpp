static void
verifySize( int NW, int NL ) {

  if ( NW != NL + 1 ) {

    Log::error( "Encountered illegal NW and NL values" );
    Log::info( "NW must be equal to NL + 1 for legendre coefficients" );
    Log::info( "NW value: {}", NW );
    Log::info( "NL value: {}", NL );
    throw std::exception();
  }
}
