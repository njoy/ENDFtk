static void
verifySize( int NPL, int NX ) {

  if ( NPL < 1 ) {

    Log::error( "Encountered empty list" );
    Log::info( "NPL should be larger than zero and equal to 6 * NX" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NX value: {}", NX );
    throw std::exception();
  }

  if ( NPL % 12 != 0 ) {

    Log::error( "Encountered inconsistent list size" );
    Log::info( "NPL must be equal to 12 * NX" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NX value: {}", NX );
    throw std::exception();
  }
}
