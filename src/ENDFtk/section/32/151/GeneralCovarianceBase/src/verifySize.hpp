static void
verifySize( int NSRS, int NLRS, int LRF ) {

  if ( NSRS < 1 ) {

    Log::error( "Encountered illegal NSRS value" );
    Log::info( "NSRS should be larger than zero" );
    Log::info( "NSRS value: {}", NSRS );
    throw std::exception();
  }
  if ( LRF != 7 ) {

    if ( NLRS < 1 ) {

      Log::error( "Encountered illegal NLRS value" );
      Log::info( "NLRS should be larger than zero" );
      Log::info( "NLRS value: {}", NLRS );
      throw std::exception();
    }
  }
}
