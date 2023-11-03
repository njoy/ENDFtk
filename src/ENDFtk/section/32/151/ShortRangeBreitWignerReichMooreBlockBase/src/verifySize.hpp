static void
verifySize( int NPL, int MPAR, int NRB ) {

  if ( NPL < 1 ) {

    Log::error( "Encountered empty list" );
    Log::info( "NPL should be larger than zero and equal to 6 * NRB" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NRB value: {}", NRB );
    throw std::exception();
  }

  if ( ( MPAR < 1 ) || ( MPAR > 5 ) ) {

    Log::error( "Encountered illegal MPAR value" );
    Log::info( "NRB should be a value between 1 and 5" );
    Log::info( "NRB value: {}", MPAR );
    throw std::exception();
  }

  if ( NRB < 1 ) {

    Log::error( "Encountered illegal NRB value" );
    Log::info( "NRB should be larger than zero" );
    Log::info( "NRB value: {}", NRB );
    throw std::exception();
  }

  if ( NPL != 6 * NRB + MPAR * NRB * ( MPAR * NRB + 1 ) / 2 ) {

    Log::error( "Encountered inconsistent list size" );
    Log::info( "NPL must be equal to 6 * NRB + MPAR * NRB * ( MPAR * NRB + 1 ) / 2" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "MPAR value: {}", MPAR );
    Log::info( "NRB value: {}", NRB );
    throw std::exception();
  }
}
