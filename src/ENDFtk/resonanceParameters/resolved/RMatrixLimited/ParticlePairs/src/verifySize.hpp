static void
verifySize( int NPL, int NPP ) {

  if ( NPL / 12. != NPP ) {

    Log::error( "Encountered inconsistent list size" );
    Log::info( "NPL must be equal to 12 * NPP" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NPP value: {}", NPP );
    throw std::exception();
  }
}
