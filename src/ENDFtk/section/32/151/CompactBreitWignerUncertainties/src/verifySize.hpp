static void
verifySize( int NPL, int NRSA ) {

  if ( NPL < 1 ) {

    Log::error( "Encountered empty list" );
    Log::info( "NPL should be larger than zero and equal to 12 * NRSA" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NRSA value: {}", NRSA );
    throw std::exception();
  }

  if ( NRSA < 1 ) {

    Log::error( "Encountered illegal NRSA value" );
    Log::info( "NRSA should be larger than zero" );
    Log::info( "NRSA value: {}", NRSA );
    throw std::exception();
  }

  if ( NPL != 12 * NRSA ) {

    Log::error( "Encountered inconsistent list size" );
    Log::info( "NPL must be equal to 12 * NRSA" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NRSA value: {}", NRSA );
    throw std::exception();
  }
}
