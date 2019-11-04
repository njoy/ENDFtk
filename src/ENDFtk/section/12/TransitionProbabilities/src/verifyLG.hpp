static void
verifyLG( int LG ) {

  if ( ( LG != 1 ) and ( LG != 2 ) ) {

    Log::error( "Encountered illegal LG value" );
    Log::info( "LG must be equal to 1 (simple case) or 2 (complex case)" );
    Log::info( "LG value: {}", LG );
    throw std::exception();
  }
}
