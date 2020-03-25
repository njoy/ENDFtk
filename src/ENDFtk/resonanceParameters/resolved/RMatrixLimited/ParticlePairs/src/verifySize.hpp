static void
verifySize( int NPL, int NPP ) {

  if ( NPL < 1 ) {

    Log::error( "Encountered empty list" );
    Log::info( "NPL should be larger than zero and equal to 12 * NPP" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NPP value: {}", NPP );
    throw std::exception();
  }

  if ( NPP < 1 ) {

    Log::error( "Encountered illegal NPP value" );
    Log::info( "NPP should be larger than zero" );
    Log::info( "NPP value: {}", NPP );
    throw std::exception();
  }

  if ( NPL / 12. != NPP ) {

    Log::error( "Encountered inconsistent list size" );
    Log::info( "NPL must be equal to 12 * NPP" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NPP value: {}", NPP );
    throw std::exception();
  }
}
