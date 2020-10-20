static void
verifySize( int NPL, int NJS ) {

  if ( NPL != 6 * NJS ) {

    Log::error( "Encountered inconsistent list size" );
    Log::info( "NPL must be equal to 6 * NJS" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NJS value: {}", NJS );
    throw std::exception();
  }
}
