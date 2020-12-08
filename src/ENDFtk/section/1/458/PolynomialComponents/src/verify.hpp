static void verify( int NPL, int NPLY ) {

  if ( NPL != ( NPLY + 1 ) * 18 ) {

    Log::error( "Encountered illegal NPL value" );
    Log::info( "NPL must be equal to {}", ( NPLY + 1 ) * 18 );
    Log::info( "NPL value: {}", NPL );
    throw std::exception();
  }

}
