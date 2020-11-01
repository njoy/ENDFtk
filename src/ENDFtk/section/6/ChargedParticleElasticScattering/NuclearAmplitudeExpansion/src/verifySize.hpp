static void
verifySize( int NW, int NL ) {

  if ( ( NW != 3 * NL + 3 ) and ( NW != 4 * NL + 3 ) ) {

    Log::error( "Encountered illegal NW and NL values" );
    Log::info( "NW must be equal to 3*NL+3 or 4*NL+3 for "
               "nuclear amplitude expansion" );
    Log::info( "NW value: {}", NW );
    Log::info( "NL value: {}", NL );
    throw std::exception();
  }
}
