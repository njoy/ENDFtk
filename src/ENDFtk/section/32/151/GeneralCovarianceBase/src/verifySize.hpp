static void
verifySize( int NSRS, int NLRS, int LRF ) {

  if ( NSRS < 0 ) {

    Log::error( "Encountered illegal NSRS value" );
    Log::info( "NSRS should be larger than or equal to zero" );
    Log::info( "NSRS value: {}", NSRS );
    throw std::exception();
  }
  if ( LRF != 7 ) {

    if ( NLRS < 0) {

      Log::error( "Encountered illegal NLRS value" );
      Log::info( "NLRS should be larger than or equal to zero" );
      Log::info( "NLRS value: {}", NLRS );
      throw std::exception();
    }
  }
  else {

    if ( NLRS != 0 ) {

      Log::error( "Encountered illegal NLRS value" );
      Log::info( "NLRS should be zero for LRF=7 and LCOMP=1" );
      Log::info( "NLRS value: {}", NLRS );
      throw std::exception();
    }
  }
}
