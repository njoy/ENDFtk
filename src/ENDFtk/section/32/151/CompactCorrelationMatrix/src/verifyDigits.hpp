static void
verifyDigits( unsigned int n ) {

  if ( ( n < 2 ) || ( n > 6 ) ) {

    Log::error( "Encountered illegal NDIGIT value" );
    Log::info( "NDIGIT should be equal to 2, 3, 4, 5 or 6" );
    Log::info( "NDIGIT value: {}", n );
    throw std::exception();
  }
}
