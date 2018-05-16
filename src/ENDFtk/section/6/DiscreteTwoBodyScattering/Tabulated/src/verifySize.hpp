static void
verifySize( int NW, int NL ) {

  if ( NW != 2 * NL ) {

    Log::error( "Encountered illegal NW and NL values" );
    Log::info( "NW must be equal to 2 * NL for tabulated cosines" );
    Log::info( "NW value: {}", NW );
    Log::info( "NL value: {}", NL );
    throw std::exception();
  }
}
