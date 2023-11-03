static void
verifySize( int NPL, int NI ) {

  if ( NPL != NI * 6 ) {

    Log::error( "Encountered illegal NPL and NI values " );
    Log::info( "NPL must be equal to 6*NI for element information data" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NI value: {}", NI );
    throw std::exception();
  }
}
