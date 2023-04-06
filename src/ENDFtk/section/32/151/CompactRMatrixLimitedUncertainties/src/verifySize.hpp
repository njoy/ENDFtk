static void
verifySize( int NJSX ) {

  if ( NJSX < 1 ) {

    Log::error( "Encountered illegal NJSX value" );
    Log::info( "NJSX should be larger than zero" );
    Log::info( "NJSX value: {}", NJSX );
    throw std::exception();
  }
}
