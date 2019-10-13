static void
verifySize( int NPL, int NX ) {

  if ( NPL % 6 != 0 ) {

    Log::error( "Encountered inconsistent list size" );
    Log::info( "NPL must be equal to 6 * NX" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NX value: {}", NX );
    throw std::exception();
  }
}
