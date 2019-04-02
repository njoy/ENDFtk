static void
verifyLANG( int LANG ) {

  if ( ( LANG != 12 ) && ( LANG != 14 ) ) {

    Log::error( "Encountered illegal LANG value" );
    Log::info( "LANG must be equal to 12 or 14 for tabulated cosines" );
    Log::info( "LANG value: {}", LANG );
    throw std::exception();
  }
}
