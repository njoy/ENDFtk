static void
verifyNT( int NT ) {

  if ( NT > 12 ) {

    Log::error( "Encountered illegal NT value" );
    Log::info( "NT can not be larger than 12" );
    Log::info( "NT value: {}", NT );
    throw std::exception();
  }
}
