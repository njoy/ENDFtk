static void
verifySize( int NW, int NL ) {

  if ( NW != NL ) {

    Log::error( "Encountered illegal NW and NL values" );
    Log::info( "NW must be equal to NL for legendre coefficients" );
    Log::info( "NW value: {}", NW );
    Log::info( "NL value: {}", NL );
    throw std::exception();
  }
}
