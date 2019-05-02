static void
verifyNC( int NC ) {

  if ( ( NC != 3 ) and ( NC != 17 ) ) {

    Log::error( "Encountered illegal NC value" );
    Log::info( "NC must be equal to either 3 or 17" );
    Log::info( "NC value: {}", NC );
    throw std::exception();
  }
}
