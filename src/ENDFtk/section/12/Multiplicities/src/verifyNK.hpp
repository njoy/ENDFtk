static void
verifyNK( int NK ) {

  if ( NK == 0 ) {

    Log::error( "Encountered illegal NK value" );
    Log::info( "NK must be at least equal to 1" );
    Log::info( "NK value: {}", NK );
    throw std::exception();
  }
}
