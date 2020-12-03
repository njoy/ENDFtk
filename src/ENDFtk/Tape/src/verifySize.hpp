static void
verifySize( int size ) {

  if ( size == 0 ) {

    Log::error( "No materials were defined" );
    Log::info( "There must be at least one material in a tape" );
    throw std::exception();
  }
}
