static void
verifySize( int NPL, int NRS ) {

  if ( NPL < 1 ) {

    Log::error( "Encountered empty list" );
    Log::info( "NPL should be larger than zero and equal to 18 * NRS" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NRS value: {}", NRS );
    throw std::exception();
  }

  if ( NRS < 1 ) {

    Log::error( "Encountered illegal NRS value" );
    Log::info( "NRS should be larger than zero" );
    Log::info( "NRS value: {}", NRS );
    throw std::exception();
  }

  if ( NPL != 18 * NRS ) {

    Log::error( "Encountered inconsistent list size" );
    Log::info( "NPL must be equal to 18 * NRS" );
    Log::info( "NPL value: {}", NPL );
    Log::info( "NRS value: {}", NRS );
    throw std::exception();
  }
}
