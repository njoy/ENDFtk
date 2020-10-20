static void
verifySize( int NJS ) {

  if ( NJS < 1 ) {

    Log::error( "Encountered illegal NJS value" );
    Log::info( "NJS should be larger than zero" );
    Log::info( "NJS value: {}", NJS );
    throw std::exception();
  }
}
