static void
verifySize( int NPL, int NRS ) {

  if ( NPL != 6 * NRS ) {

    Log::error( "Encountered inconsistent list size" );
    Log::info( "NPL must be equal to 6 * NRS" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NRS value: {}", NRS );
    throw std::exception();
  }
}
