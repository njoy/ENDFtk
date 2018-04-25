static void
verifyLTP( int LTP ) {

  if ( LTP != 1 ) {

    Log::error( "Encountered illegal LTP value" );
    Log::info( "LTP must be equal to 1 for nuclear amplitude expansion" );
    Log::info( "LTP value: {}", LTP );
    throw std::exception();
  }
}
