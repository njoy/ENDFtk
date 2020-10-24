static void
verifyLTP( int LTP ) {

  if ( LTP != 2 ) {

    Log::error( "Encountered illegal LTP value" );
    Log::info( "LTP must be equal to 2 for legendre coefficients" );
    Log::info( "LTP value: {}", LTP );
    throw std::exception();
  }
}
