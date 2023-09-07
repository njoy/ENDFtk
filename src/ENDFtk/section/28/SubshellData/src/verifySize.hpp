static void
verifySize( int NPL, int NTR ) {

  if ( NPL != ( NTR + 1 ) * 6 ) {

    Log::error( "Encountered illegal NPL and NTR values " );
    Log::info( "NPL must be equal to 6*NTR+6 for fission yield data" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NTR value: {}", NTR );
    throw std::exception();
  }
}
