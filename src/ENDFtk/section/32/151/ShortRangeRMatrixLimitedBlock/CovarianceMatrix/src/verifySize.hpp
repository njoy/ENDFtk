static void
verifySize( int NPL, int NPARB ) {

  if ( NPL < 1 ) {

    Log::error( "Encountered empty list" );
    Log::info( "NPL should be larger than zero and equal to NPARB * ( NPARB + 1 ) / 2" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NPARB value: {}", NPARB );
    throw std::exception();
  }

  if ( NPARB < 1 ) {

    Log::error( "Encountered illegal NPARB value" );
    Log::info( "NPARB should be larger than zero" );
    Log::info( "NPARB value: {}", NPARB );
    throw std::exception();
  }

  if ( NPL != NPARB * ( NPARB + 1 ) / 2 ) {

    Log::error( "Encountered inconsistent list size" );
    Log::info( "NPL must be equal to NPARB * ( NPARB + 1 ) / 2" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NPARB value: {}", NPARB );
    throw std::exception();
  }
}
