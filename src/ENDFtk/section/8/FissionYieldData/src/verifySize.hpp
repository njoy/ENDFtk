static void
verifySize( int NPL, int NFP ) {

  if ( NPL != NFP * 4 ) {

    Log::error( "Encountered illegal NPL and NFP values " );
    Log::info( "NPL must be equal to 4*NFP for fission yield data" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NFP value: {}", NFP );
    throw std::exception();
  }
}
