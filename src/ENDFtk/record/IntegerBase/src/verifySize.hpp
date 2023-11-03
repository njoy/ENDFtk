static void
verifySize( unsigned int size ) {

  if ( size > N ) {

    Log::error( "Too many K values for INTG record with NDIGIT = {}", NDIGIT );
    Log::info( "Expected at most: {}", N );
    Log::info( "Got: {}", size );
    throw std::exception();
  }
}
