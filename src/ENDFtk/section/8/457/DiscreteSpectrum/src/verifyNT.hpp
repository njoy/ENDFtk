static void
verifyNT( int NT ) {

  if ( ( NT != 4 ) && ( NT != 6 ) && ( NT != 12 ) ) {

    Log::error( "Encountered illegal NT value" );
    Log::info( "NT can only be equal to 4, 6 or 12" );
    Log::info( "NT value: {}", NT );
    throw std::exception();
  }
}
