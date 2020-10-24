static void
verifyLANG( int LANG ) {

  if ( LANG != 0 ) {

    Log::error( "Encountered illegal LANG value" );
    Log::info( "LANG must be equal to 0 for legendre coefficients" );
    Log::info( "LANG value: {}", LANG );
    throw std::exception();
  }
}
