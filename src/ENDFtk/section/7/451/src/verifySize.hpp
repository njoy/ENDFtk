static void
verifySize( unsigned int NA ) {

  if ( NA == 0 ) {

    Log::error( "Encountered illegal NA value" );
    Log::info( "NA must be greater than or equal to 1" );
    Log::info( "NA value: {}", NA );
    throw std::exception();
  }
}
