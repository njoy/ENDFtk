static void
verifyLT( int LT, int NT ) {

  if ( LT != NT - 1 ) {

    Log::error( "Encountered illegal LT value" );
    Log::info( "LT must be equal to the number of temperatures NT - 1" );
    Log::info( "LT value: {}", LT );
    Log::info( "NT value: {}", NT );
    throw std::exception();
  }
}
