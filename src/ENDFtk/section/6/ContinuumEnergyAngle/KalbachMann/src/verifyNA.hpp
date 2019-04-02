static void
verifyNA( int NA ) {

  if ( ( NA != 1 ) && ( NA != 2 ) ) {

    Log::error( "Encountered illegal NA value for Kalbach-Mann" );
    Log::info( "NA must be equal to 1 or 2" );
    Log::info( "NA value: {}", NA );
    throw std::exception();
  }
}
