static void
verifyNK( int NK ) {

  if ( NK == 0 ) {

    Log::error( "No partial distributions were defined" );
    Log::info( "NK must be non zero" );
    throw std::exception();
  }
}
