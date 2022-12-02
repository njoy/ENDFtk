static void
verifyDigits( unsigned int n ) {

  if ( ( n < 2 ) || ( n > 6 ) ) {

    Log::error( "Encountered illegal NDIGITS value" );
    Log::info( "NDIGITS should be equal to 2, 3, 4, 5 or 6" );
    Log::info( "NDIGITS value: {}", n );
    throw std::exception();
  }
}
