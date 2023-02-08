static void
verifySize( int NPL, int NPAR ) {

  if ( NPL < 1 ) {

    Log::error( "Encountered empty list" );
    Log::info( "NPL should be larger than zero and equal to NPAR * ( NPAR + 1 ) / 2" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NPAR value: {}", NPAR );
    throw std::exception();
  }

  if ( NPAR < 1 ) {

    Log::error( "Encountered illegal NPAR value" );
    Log::info( "NPAR should be larger than zero" );
    Log::info( "NPAR value: {}", NPAR );
    throw std::exception();
  }

  if ( NPL != NPAR * ( NPAR + 1 ) / 2 ) {

    Log::error( "Encountered inconsistent list size" );
    Log::info( "NPL must be equal to NPAR * ( NPAR + 1 ) / 2" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NPAR value: {}", NPAR );
    throw std::exception();
  }
}
